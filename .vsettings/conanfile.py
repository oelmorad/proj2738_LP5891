#! /usr/bin/python3

# standard modules imports
import hashlib
import json
import os
from concurrent.futures import ThreadPoolExecutor
from enum import StrEnum
from functools import lru_cache, wraps
from itertools import groupby, product
from pathlib import Path
from shutil import copyfile, copystat
from typing import Annotated, Any, Iterable, Optional, Self

# conan imports
from conan import ConanFile
from conan.tools.files import save

# external modules import
from more_itertools import partition
from pydantic import (
    AliasGenerator,
    BaseModel,
    ConfigDict,
    Field,
    PrivateAttr,
    StringConstraints,
    field_validator,
    model_validator,
)
from ruamel.yaml import YAML

# ============================================================================ #
# types and constants

PACKAGE_DATA_FILE_NAME = "vconan_pkg_data.json"
REQUIRED_PARAMETER = ...

NonEmptyString = Annotated[str, StringConstraints(min_length=1)]


class StrEnumCaseless(StrEnum):
    @classmethod
    def _missing_(cls, value: str):
        """Used to look up for values not found in cls; thus, allowing one to try and find the enum member by value.

        Adapted from: https://stackoverflow.com/questions/76129550/how-to-make-case-insensitive-choices-using-pythons-enum-and-fastapi
        """

        value_lower = value.lower()

        for member in cls:
            if member.lower() == value_lower:
                return member

        return None


class PROGRAMMING_LANGUAGE(StrEnumCaseless):
    C = "C"
    CPP = "CXX"
    ASM = "ASM"
    MATLAB = "Matlab"
    SIMULINK = "Simulink"

    @classmethod
    def _missing_(cls, value: str):
        value_lower = value.lower()

        if value_lower in ["cpp", "c++"]:
            return cls.CPP

        if value_lower in ["assembly"]:
            return cls.ASM

        return super()._missing_(value)


class BUSINESS_GROUP(StrEnum):
    VCORE = "V-Core"
    CDA = "CDA"
    VIS = "VIS"
    PTS = "PTS"
    THS = "THS"


class REPOSITROY_TYPE(StrEnumCaseless):
    GIT = "GIT"
    SVN = "SVN"


class OUTPUT_TYPE(StrEnumCaseless):
    SOURCE = "source-code"
    STATIC_LIBRARY = "static-library"
    SHARED_LIBRARY = "shared-library"
    EXECUTABLE = "executable"


class BUILD_TYPE(StrEnumCaseless):
    DEBUG = "Debug"
    RELEASE = "Release"
    RELWITHDEBINFO = "RelWithDebInfo"
    MINSIZEREL = "MinSizeRel"


# ============================================================================ #
# generic field validators


def parse_items(item, needed_keys: list[str]) -> list[dict]:
    if not isinstance(item, dict):
        return [{needed_keys[0]: item}]

    if len(item.keys()) != 1:
        return [item]

    key, value = list(item.items())[0]

    if key == needed_keys[0]:
        return [{key: value}]

    if len(needed_keys) == 1:
        return [{needed_keys[0]: item}]

    next_item = parse_items(value, needed_keys[1:])

    if isinstance(key, tuple):
        return [{needed_keys[0]: k, **v} for k in key for v in next_item]

    return [{needed_keys[0]: key, **v} for v in next_item]


def expand_dict_combinations(item: dict) -> list[dict]:
    keys, values = zip(*item.items())
    keys = list(keys)
    values = list(values)
    values = [v if isinstance(v, tuple) else (v,) for v in values]

    return [dict(zip(keys, combination)) for combination in product(*values)]


# ============================================================================ #
# models


class ConfiguredBaseModel(BaseModel):
    model_config = ConfigDict(
        # populate_by_name=True,
        use_enum_values=True,
        extra="forbid",
        alias_generator=AliasGenerator(
            validation_alias=lambda field_name: field_name.replace("_", "-")
        ),
        validate_default=True,
    )

    def __hash__(self) -> int:  # make hashable BaseModel subclass
        """
        from: https://stackoverflow.com/questions/63721614/unhashable-type-in-fastapi-request
        """
        return hash((type(self),) + tuple(self.__dict__.values()))

    @model_validator(mode="before")
    @classmethod
    def remove_none_values(cls, data: dict) -> dict:
        """
        If the model is being validated with fields that are set to None or empty string;
        omit that field and let it be set to it's default value
        """
        return {
            key: value
            for key, value in data.items()
            if ((value is not None) and (value != ""))
        }


class FilePatternEntry(ConfiguredBaseModel):
    pattern: NonEmptyString = Field(
        REQUIRED_PARAMETER,
    )
    excludes: Optional[tuple[NonEmptyString, ...]] = Field(
        default_factory=tuple,
        validation_alias="exclude",
    )

    # NOTE: order of the field validators is important
    #       "before" mode validators are executed in reverse order they are defined
    #       "after" mode validators are executed in the order they are defined

    # <------------- "before" mode validators ------------->

    # <------------- "after" mode validators ------------->

    @model_validator(mode="after")
    def adjust_separators(self) -> Self:
        self.pattern = self.pattern.replace("/", os.path.sep).replace("\\", os.path.sep)

        self.excludes = tuple(
            x.replace("/", os.path.sep).replace("\\", os.path.sep)
            for x in self.excludes
        )

        return self


class BuildFlagsEntry(ConfiguredBaseModel):
    flags: str = Field(
        REQUIRED_PARAMETER,
    )
    files: Optional[list[FilePatternEntry]] = Field(
        default_factory=list,
    )

    # NOTE: order of the field validators is important
    #       "before" mode validators are executed in reverse order they are defined
    #       "after" mode validators are executed in the order they are defined

    # <------------- "before" mode validators ------------->

    @field_validator(
        "files",
        mode="before",
    )
    @classmethod
    def expand_tuples(cls, field_value: list[dict]) -> list[dict]:
        if field_value is None:
            return field_value

        result = []
        for item in field_value:
            result.extend(expand_dict_combinations(item))

        return result

    @field_validator(
        "files",
        mode="before",
    )
    @classmethod
    def cast_files_entries_to_dict(cls, field_value) -> list[dict] | None:
        if field_value is None:
            return field_value

        # return parse_list_of_dict(field_value, "pattern")

        parsed = []
        for item in field_value:
            parsed.extend(parse_items(item, ["pattern", "exclude"]))

        return parsed

    @field_validator(
        "files",
        mode="before",
    )
    @classmethod
    def cast_single_to_list(cls, field_value) -> list | None:
        if field_value is None:
            return field_value

        if not isinstance(field_value, list):
            return [field_value]

        return field_value

    # <------------- "after" mode validators ------------->

    @field_validator(
        "files",
        mode="after",
    )
    @classmethod
    def distrubute_excludes(cls, field_value: list) -> list:
        default_patterns = [
            FilePatternEntry(pattern="!./.vsettings/conanfile.py"),
            FilePatternEntry(pattern="!./.git/**/*"),
        ]

        # partition the path_list into included_patterns and excluded_patterns
        included_patterns, excluded_patterns = partition(
            lambda x: x.pattern.startswith("!"),
            field_value + default_patterns,
        )

        excluded_patterns = tuple(
            path_pattern.pattern[1:] for path_pattern in excluded_patterns
        )

        result = list(included_patterns)
        for i in range(len(result)):
            if result[i].excludes is None:
                result[i].excludes = tuple()

            result[i].excludes += excluded_patterns

        return result


class DependencyEntry(ConfiguredBaseModel):
    dependency_reference: NonEmptyString = Field(
        REQUIRED_PARAMETER,
    )
    configuration: Optional[str] = Field(
        default=None,
    )

    # NOTE: order of the field validators is important
    #       "before" mode validators are executed in reverse order they are defined
    #       "after" mode validators are executed in the order they are defined

    # <------------- "before" mode validators ------------->

    # <------------- "after" mode validators ------------->


class ManifestConfiguration(ConfiguredBaseModel):
    base_configuration: Optional[str] = Field(
        default=None,
    )
    dependencies: Optional[list[DependencyEntry]] = Field(
        default_factory=list,
    )
    tools_dependencies: Optional[list[DependencyEntry]] = Field(
        default_factory=list,
    )

    output_type: OUTPUT_TYPE = Field(
        REQUIRED_PARAMETER,
    )
    compiler: Optional[str] = Field(
        default="",
    )
    compiler_version: Optional[str] = Field(
        default="",
    )
    hw_architecture: Optional[str] = Field(
        default=None,
    )
    sw_architecture: Optional[list[NonEmptyString]] = Field(
        default_factory=list,
    )

    src_paths: Optional[list[FilePatternEntry]] = Field(
        default_factory=list,
    )
    inc_paths_public: Optional[list[FilePatternEntry]] = Field(
        default_factory=list,
    )
    inc_paths_private: Optional[list[FilePatternEntry]] = Field(
        default_factory=list,
    )
    lib_paths: Optional[list[FilePatternEntry]] = Field(
        default_factory=list,
    )
    assembly_paths: Optional[list[FilePatternEntry]] = Field(
        default_factory=list,
    )
    artifacts_paths: Optional[list[FilePatternEntry]] = Field(
        default_factory=list,
    )
    docs_paths: Optional[list[FilePatternEntry]] = Field(
        default_factory=list,
    )
    cfg_src_paths: Optional[list[FilePatternEntry]] = Field(
        default_factory=list,
    )
    cfg_inc_paths_private: Optional[list[FilePatternEntry]] = Field(
        default_factory=list,
    )
    cfg_inc_paths_public: Optional[list[FilePatternEntry]] = Field(
        default_factory=list,
    )
    cfg_artifacts_paths: Optional[list[FilePatternEntry]] = Field(
        default_factory=list,
    )
    shared_src_paths: Optional[list[FilePatternEntry]] = Field(
        default_factory=list,
    )
    shared_inc_paths_private: Optional[list[FilePatternEntry]] = Field(
        default_factory=list,
    )
    shared_inc_paths_public: Optional[list[FilePatternEntry]] = Field(
        default_factory=list,
    )
    shared_artifacts_paths: Optional[list[FilePatternEntry]] = Field(
        default_factory=list,
    )

    compiler_flags: Optional[list[BuildFlagsEntry]] = Field(
        default_factory=list,
    )
    assembler_flags: Optional[list[BuildFlagsEntry]] = Field(
        default_factory=list,
    )
    linker_flags: Optional[list[NonEmptyString]] = Field(
        default_factory=list,
    )
    linker_script: Optional[Path] = Field(
        default=None,
    )

    toolchain_file: Optional[Path] = Field(
        default=None,
    )
    build_type: Optional[BUILD_TYPE] = Field(
        default=None,
    )

    # NOTE: order of the field validators is important
    #       "before" mode validators are executed in reverse order they are defined
    #       "after" mode validators are executed in the order they are defined

    # <------------- "before" mode validators ------------->

    @field_validator(
        "dependencies",
        "tools_dependencies",
        "src_paths",
        "inc_paths_private",
        "inc_paths_public",
        "lib_paths",
        "assembly_paths",
        "artifacts_paths",
        "docs_paths",
        "cfg_src_paths",
        "cfg_inc_paths_private",
        "cfg_inc_paths_public",
        "cfg_artifacts_paths",
        "shared_src_paths",
        "shared_inc_paths_private",
        "shared_inc_paths_public",
        "shared_artifacts_paths",
        "compiler_flags",
        "assembler_flags",
        mode="before",
    )
    @classmethod
    def expand_tuples(cls, field_value: list[dict]) -> list[dict]:
        if field_value is None:
            return field_value

        result = []
        for item in field_value:
            result.extend(expand_dict_combinations(item))

        return result

    @field_validator(
        "dependencies",
        "tools_dependencies",
        mode="before",
    )
    @classmethod
    def cast_dependency_entries_to_dict(cls, field_value) -> list[dict] | None:
        if field_value is None:
            return field_value

        # return parse_list_of_dict(field_value, "dependency-reference")

        parsed = []
        for item in field_value:
            # parsed.extend(parse_items(item, ["dependency-reference", "configuration"]))
            items = parse_items(item, ["dependency-reference", "configuration"])

            parsed.extend(items)

        return parsed

    @field_validator(
        "src_paths",
        "inc_paths_private",
        "inc_paths_public",
        "lib_paths",
        "assembly_paths",
        "artifacts_paths",
        "docs_paths",
        "cfg_src_paths",
        "cfg_inc_paths_private",
        "cfg_inc_paths_public",
        "cfg_artifacts_paths",
        "shared_src_paths",
        "shared_inc_paths_private",
        "shared_inc_paths_public",
        "shared_artifacts_paths",
        mode="before",
    )
    @classmethod
    def cast_files_entries_to_dict(cls, field_value) -> list[dict] | None:
        if field_value is None:
            return field_value

        # return parse_list_of_dict(field_value, "pattern")

        parsed = []
        for item in field_value:
            parsed.extend(parse_items(item, ["pattern", "exclude"]))

        return parsed

    @field_validator(
        "compiler_flags",
        "assembler_flags",
        mode="before",
    )
    @classmethod
    def cast_flags_entries_to_dict(cls, field_value) -> list[dict] | None:
        if field_value is None:
            return field_value

        # return parse_list_of_dict(field_value, "flags")\

        parsed = []
        for item in field_value:
            parsed.extend(parse_items(item, ["flags", "files"]))

        return parsed

    @field_validator(
        "dependencies",
        "tools_dependencies",
        "src_paths",
        "inc_paths_private",
        "inc_paths_public",
        "lib_paths",
        "assembly_paths",
        "artifacts_paths",
        "docs_paths",
        "cfg_src_paths",
        "cfg_inc_paths_private",
        "cfg_inc_paths_public",
        "cfg_artifacts_paths",
        "shared_src_paths",
        "shared_inc_paths_private",
        "shared_inc_paths_public",
        "shared_artifacts_paths",
        "compiler_flags",
        "assembler_flags",
        mode="before",
    )
    @classmethod
    def cast_single_to_list(cls, field_value) -> list | None:
        if field_value is None:
            return field_value

        if not isinstance(field_value, list):
            return [field_value]

        return field_value

    # <------------- "after" mode validators ------------->

    @field_validator(
        "artifacts_paths",
        mode="after",
    )
    @classmethod
    def add_vsettings(cls, field_value: list) -> list:
        patterns = [
            FilePatternEntry(pattern="./.vsettings/**/*"),
        ]

        return field_value + patterns

    @field_validator(
        "src_paths",
        "inc_paths_public",
        "inc_paths_public",
        "lib_paths",
        "assembly_paths",
        "artifacts_paths",
        "docs_paths",
        "cfg_src_paths",
        "cfg_inc_paths_private",
        "cfg_inc_paths_public",
        "cfg_artifacts_paths",
        "shared_src_paths",
        "shared_inc_paths_private",
        "shared_inc_paths_public",
        "shared_artifacts_paths",
        mode="after",
    )
    @classmethod
    def distrubute_excludes(cls, field_value: list) -> list:
        default_patterns = [
            FilePatternEntry(pattern="!./.vsettings/conanfile.py"),
            FilePatternEntry(pattern="!./.git/**/*"),
        ]

        # partition the path_list into included_patterns and excluded_patterns
        included_patterns, excluded_patterns = partition(
            lambda x: x.pattern.startswith("!"),
            field_value + default_patterns,
        )

        excluded_patterns = tuple(
            path_pattern.pattern[1:] for path_pattern in excluded_patterns
        )

        result = list(included_patterns)
        for i in range(len(result)):
            if result[i].excludes is None:
                result[i].excludes = tuple()

            result[i].excludes += excluded_patterns

        return result

    @field_validator(
        "toolchain_file",
        mode="after",
    )
    @classmethod
    def resolve_toolchain_path(cls, field_value: Path) -> Path:
        if field_value is None:
            return field_value

        if not field_value.is_absolute():
            field_value = (Path(__file__).parent / field_value).resolve()

        return field_value


class ManifestData(ConfiguredBaseModel):
    name: NonEmptyString = Field(
        REQUIRED_PARAMETER,
    )
    version: NonEmptyString = Field(
        REQUIRED_PARAMETER,
    )
    user: Optional[str] = Field(
        default="",
    )
    channel: Optional[str] = Field(
        default="",
    )

    programming_languages: set[PROGRAMMING_LANGUAGE] = Field(
        REQUIRED_PARAMETER, min_length=1
    )
    description: Optional[Annotated[str, StringConstraints(max_length=300)]] = Field(
        default="",
    )

    business_group: BUSINESS_GROUP = Field(
        default=REQUIRED_PARAMETER,
    )
    product_group: Optional[str] = Field(
        default=None,
    )
    product_line: Optional[str] = Field(
        default=None,
    )
    domain: Optional[list[NonEmptyString]] = Field(
        default_factory=list,
    )
    software_layer: Optional[str] = Field(
        default=None,
    )
    safety_level: Optional[str] = Field(
        default=None,
    )
    license_type: Optional[str] = Field(
        default=None,
    )
    project_homepage: Optional[str] = Field(
        default=None,
    )
    repository_link: Optional[str] = Field(
        default=None,
    )
    repository_type: Optional[REPOSITROY_TYPE] = Field(
        default=None,
    )

    output_folder: NonEmptyString = Field(
        default="conan_out",
    )
    default_conf: NonEmptyString = Field(
        default=REQUIRED_PARAMETER,
    )

    configurations: dict[NonEmptyString, ManifestConfiguration] = Field(
        default=REQUIRED_PARAMETER,
    )

    custom_attributes: Optional[dict[str, Any]] = Field(
        default_factory=dict,
    )

    manifest_template_version: NonEmptyString = Field(
        default=REQUIRED_PARAMETER,
    )

    # NOTE: order of the field validators is important
    #       "before" mode validators are executed in reverse order they are defined
    #       "after" mode validators are executed in the order they are defined

    # <------------- "before" mode validators ------------->

    # <------------- "after" mode validators ------------->

    @field_validator("configurations", mode="after")
    @classmethod
    def base_conf_checker(
        cls, field_value: dict[str, ManifestConfiguration]
    ) -> dict[str, ManifestConfiguration]:
        for conf_name, conf in field_value.items():
            if conf.base_configuration is None:
                continue

            if conf.base_configuration not in field_value.keys():
                raise ValueError(
                    f"Base configuration for {conf_name}: {conf.base_configuration} is not defined."
                )

        return field_value

    @field_validator("configurations", mode="after")
    @classmethod
    def base_conf_handler(
        cls, field_value: dict[str, ManifestConfiguration]
    ) -> dict[str, ManifestConfiguration]:
        result = {
            conf_name: conf.model_copy(deep=True)
            for conf_name, conf in field_value.items()
        }

        for conf_name, conf in field_value.items():
            base_conf_name = conf.base_configuration
            if base_conf_name is None:
                continue

            base_conf = field_value[base_conf_name]

            for field_name in base_conf.model_fields.keys():
                if getattr(conf, field_name):
                    continue

                setattr(
                    result[conf_name],
                    field_name,
                    getattr(base_conf, field_name),
                )

        return result

    @model_validator(mode="after")
    def default_conf_existence_validator(self) -> Self:
        if self.default_conf not in self.configurations.keys():
            raise ValueError(
                f"Default configuration: ({self.default_conf}) does not exist"
            )

        return self

    # ------------------------------------------------------------------------ #

    _current_configuration: ManifestConfiguration = PrivateAttr(default=None)

    def set_conf(self, conf_name: str) -> None:
        self._current_configuration = self.configurations[conf_name]

    def get_conf(self) -> ManifestConfiguration:
        if self._current_configuration is None:
            raise ValueError("Configuration not set.")

        return self._current_configuration

    def get_all_path_patterns(self) -> list[FilePatternEntry]:
        result = set()

        for conf in self.configurations.values():
            result.update(conf.src_paths)
            result.update(conf.inc_paths_private)
            result.update(conf.inc_paths_public)
            result.update(conf.lib_paths)
            result.update(conf.assembly_paths)
            result.update(conf.artifacts_paths)
            result.update(conf.docs_paths)
            result.update(conf.cfg_src_paths)
            result.update(conf.cfg_inc_paths_private)
            result.update(conf.cfg_inc_paths_public)
            result.update(conf.cfg_artifacts_paths)
            result.update(conf.shared_src_paths)
            result.update(conf.shared_inc_paths_private)
            result.update(conf.shared_inc_paths_public)
            result.update(conf.shared_artifacts_paths)

        return list(result)


# ============================================================================ #


def custom_lru_cache(maxsize=128, typed=False):
    """
    A custom version of the `functools.lru_cache` decorator that doesn't cache Falsey results
    and recomputes them on subsequent calls.

    Based on: https://stackoverflow.com/questions/71175293/make-built-in-lru-cache-skip-caching-when-function-returns-none
    """

    # define custom exception to be caught
    class CustomFalseyValueException(Exception):
        def __init__(self, value: Any, *args: object) -> None:
            super().__init__(*args)

            self.value = value

    def decorator(func):
        @lru_cache(maxsize=maxsize, typed=typed)
        def raise_exception_wrapper(*args, **kwargs):
            value = func(*args, **kwargs)

            # don't cache if the value is Falsey
            if not value:
                raise CustomFalseyValueException(value)

            return value

        @wraps(func)
        def handle_exception_wrapper(*args, **kwargs):
            try:
                return raise_exception_wrapper(*args, **kwargs)
            except CustomFalseyValueException as e:
                return e.value

        handle_exception_wrapper.cache_info = raise_exception_wrapper.cache_info
        handle_exception_wrapper.cache_clear = raise_exception_wrapper.cache_clear
        return handle_exception_wrapper

    # to handle the case where cached function is supplied directly
    if callable(maxsize):
        user_function, maxsize = maxsize, 128
        return decorator(user_function)

    return decorator


# ============================================================================ #


class BasicConanFile(ConanFile):
    virtualbuildenv = False
    virtualrunenv = False

    ## binary model
    settings = []
    options = {
        "configuration": [None, "ANY"],
        "output-type": [
            "source-code",
            "static-library",
            "shared-library",
            "executable",
        ],
    }
    default_options = {
        "configuration": None,
        # "output-type": None,
    }
    options_description = {
        "output-type": (
            "This option determines how the package is built and packaged."
        ),
        "configuration": (
            "The manifest configuration to be used in conan commands like `conan build`."
        ),
    }

    def init(self):
        self._announce_method_call("init")

        ## parse conan attributes from datafiles
        manifest_path = Path(__file__).parent / "manifest.yaml"
        manifest_data_raw = YAML(typ="safe", pure=True).load(manifest_path)
        self.datafiles = ManifestData(**manifest_data_raw)

        # Conan Attributes
        ## package reference
        self.name = self.datafiles.name
        self.version = self.datafiles.version
        self.user = self.datafiles.user
        self.channel = self.datafiles.channel
        ## metadata
        self.description = self.datafiles.description
        license = self.datafiles.license_type
        self.topics: tuple[str] = tuple(
            x
            for x in (
                self.datafiles.business_group,
                self.datafiles.product_group,
                self.datafiles.product_line,
                *self.datafiles.domain,
                self.datafiles.software_layer,
                self.datafiles.safety_level,
                self.datafiles.license_type,
                *self.datafiles.programming_languages,
                self.datafiles.repository_type,
                *[
                    self.datafiles.configurations[cfg_name].output_type
                    for cfg_name in self.datafiles.configurations.keys()
                ],
                *[
                    self.datafiles.configurations[cfg_name].compiler
                    for cfg_name in self.datafiles.configurations.keys()
                ],
                *[
                    self.datafiles.configurations[cfg_name].hw_architecture
                    for cfg_name in self.datafiles.configurations.keys()
                ],
                *[
                    sw_arch
                    for cfg_name in self.datafiles.configurations.keys()
                    for sw_arch in self.datafiles.configurations[
                        cfg_name
                    ].sw_architecture
                ],
            )
            if x  # if value is true-ish
        )
        self.homepage = self.datafiles.project_homepage
        self.url = self.datafiles.repository_link
        ## requirements
        ## sources
        self.exports = ("manifest.yaml",)
        ## binary model
        ## build
        self.build_policy = "missing"
        ## folders and layout
        self.no_copy_source = True
        ## layout
        ## package information for consumers
        ## other

    def config_options(self):
        self._announce_method_call("config_options")

    def configure(self):
        self._announce_method_call("configure")

        # set configuration to manifest value if not provided by the user
        self._set_default_option("configuration", self.datafiles.default_conf)
        configuration_name = self.options.get_safe("configuration").value
        assert configuration_name in self.datafiles.configurations.keys()
        self.datafiles.set_conf(configuration_name)

        # set output-type from configuration
        if self.options.get_safe("output-type"):
            self.output.error("output-type options MUST NOT be set by the user.")
            raise ValueError("output-type options MUST NOT be set by the user.")
        self._set_default_option("output-type", self.datafiles.get_conf().output_type)

        if self.datafiles.get_conf().output_type == "source-code":
            # set conan attributes based on options
            self.package_type = "build-scripts"  # dependencies of this type are not isntalled unless explicitly stated
            self.generators = [
                "DuplicateHeaderChecker",
            ]

        elif self.datafiles.get_conf().output_type in [
            "static-library",
            "shared-library",
            "executable",
        ]:
            # set conan attributes based on options
            self.package_type = "unknown"
            self.generators = [
                "CMakeLists",
                "CMakeConfigPkg",
                "CMakeTC",
                "DuplicateHeaderChecker",
            ]

        else:
            msg = f"Unrecognized output-type: {self.datafiles.get_conf().output_type}"
            self.output.error(msg)
            raise ValueError(msg)

    def export_sources(self):
        self._announce_method_call("export_sources", minimal=True)
        patterns = self.datafiles.get_all_path_patterns()

        root_source_folder = str(Path(self.recipe_folder).parent)

        self._copy_pattern_list(
            patterns, root_source_folder, self.export_sources_folder
        )
        return

    def layout(self):
        self._announce_method_call("layout")
        configuration = str(self.options.get_safe("configuration"))

        self.folders.root = ".."
        self.folders.source = "."
        self.folders.build = os.path.join(configuration, "build")
        self.folders.generators = os.path.join(configuration, "generators")
        self.folders.install = os.path.join(configuration, "install")

        # make packaged static library dependencies visible to consumers
        # TODO: revise
        if self.datafiles.get_conf().output_type in [
            "static-library",
            "shared-library",
        ]:
            self.cpp.package.libs = [self.name]
            self.cpp.package.libdirs = ["lib"]  # defaults for CMake install
            self.cpp.package.bindirs = ["bin"]  # defaults for CMake install

            # self.cpp.source.includedirs = [
            #     Path(path).parent
            #     for paths_list in (
            #         "inc-paths-private",
            #         "inc-paths-public",
            #         "shared-inc-paths-private",
            #         "shared-inc-paths-public",
            #         "cfg-inc-paths-private",
            #         "cfg-inc-paths-public",
            #     )
            #     for path in self.datafiles[paths_list]
            # ]
            self.cpp.build.libdirs = ["."]
            self.cpp.build.bindirs = ["."]

            # self.cpp.package.builddirs.append("lib/cmake")

        # self.cpp.source.srcdirs = [
        #     Path(x).parent for x in self.datafiles.get_all_paths()
        # ]

        self.cpp.package.set_property("datafiles", self.datafiles)
        return

    def requirements(self):
        self._announce_method_call("requirements")

        if self.datafiles.get_conf().output_type == "source-code":
            # source-code packages always get all dependencies
            for dep_entry in self.datafiles.get_conf().dependencies:
                dep_options = (
                    {"configuration": dep_entry.configuration}
                    if dep_entry.configuration
                    else None
                )
                self.requires(
                    dep_entry.dependency_reference,
                    options=dep_options,
                    headers=True,
                    libs=True,
                    transitive_headers=True,
                    transitive_libs=True,
                    run=True,
                    visible=True,
                )
        else:
            for dep_entry in self.datafiles.get_conf().dependencies:
                dep_options = (
                    {"configuration": dep_entry.configuration}
                    if dep_entry.configuration
                    else None
                )
                self.requires(
                    dep_entry.dependency_reference,
                    options=dep_options,
                )

        for dep_entry in self.datafiles.get_conf().tools_dependencies:
            dep_options = (
                {"configuration": dep_entry.configuration}
                if dep_entry.configuration
                else None
            )
            self.tool_requires(
                dep_entry.dependency_reference,
                options=dep_options,
            )

    def source(self):
        self._announce_method_call("source", minimal=True)

        return

    def generate(self):
        self._announce_method_call("generate")

        ## Add .gitignore to base_build folder
        if ".gitignore" not in os.listdir(self.folders.base_build):
            save(
                self,
                path=os.path.join(self.folders.base_build, ".gitignore"),
                content="# <---- CONAN AUTOGENERATED ---->\n*\n!cfg/**",
            )

        if self.datafiles.get_conf().output_type == "source-code":
            self.output.warning("source-code package")
            return

        return

    def build(self):
        self._announce_method_call("build")

        if self.datafiles.get_conf().output_type == "source-code":
            self.output.warning(
                "source-code package does not build. No action performed."
            )
            return

        # create build folder if it doesn't exist
        os.makedirs(self.build_folder, exist_ok=True)

        # get conf
        # NOBUG: default value because configuration name is subject to change
        build_jobs = self.conf.get("user.valeo.build:jobs", os.cpu_count())
        cmake_generator = self.conf.get("user.valeo.build:cmake_generator", "Ninja")

        # check if kwinject command needed
        kwinject = self.conf.get("user.valeo.kwbuild:kwinject")

        # kwinject configurations
        kwinject_output = self.conf.get("user.valeo.kwbuild:output")
        kwinject_prog = self.conf.get("user.valeo.kwbuild:prog")
        kwinject_conf = self.conf.get("user.valeo.kwbuild:kwconf")

        if kwinject:
            command_parts = [
                f"kwinject",
                (f"--output" if kwinject_output is not None else ""),
                (f"{kwinject_output}" if kwinject_output is not None else ""),
                (f"--prog" if kwinject_prog is not None else ""),
                (f"{kwinject_prog}" if kwinject_prog is not None else ""),
                (f"-c" if kwinject_conf is not None else ""),
                (f"{kwinject_conf}" if kwinject_conf is not None else ""),
                f"cmake",
                f'-G "{cmake_generator}"',
                f'-DCMAKE_PREFIX_PATH:PATH="{self.generators_folder}"',
                f'-DCMAKE_MODULE_PATH:PATH="{self.generators_folder}"',
                f'-DCMAKE_TOOLCHAIN_FILE:FILEPATH="{os.path.join(self.generators_folder, "TC-Conan.cmake")}"',
            ]
        else:
            command_parts = [
                f"cmake",
                f'-G "{cmake_generator}"',
                f'-DCMAKE_PREFIX_PATH:PATH="{self.generators_folder}"',
                f'-DCMAKE_MODULE_PATH:PATH="{self.generators_folder}"',
                f'-DCMAKE_TOOLCHAIN_FILE:FILEPATH="{os.path.join(self.generators_folder, "TC-Conan.cmake")}"',
            ]

        if self.package_folder:
            command_parts.append(f'-DCMAKE_INSTALL_PREFIX:PATH="{self.package_folder}"')
        if self.datafiles.get_conf().build_type:
            command_parts.append(
                f"-DCMAKE_BUILD_TYPE={self.datafiles.get_conf().build_type}"
            )

        # Run CMake to configure then build
        command_parts.append(f'"{self.generators_folder}"')
        self.run(" ".join(command_parts), cwd=self.build_folder)
        self.run(
            f'cmake --build "{self.build_folder}" -- -j{build_jobs}',
            cwd=self.build_folder,
        )

        return

    def package(self):
        self._announce_method_call("package")

        os.makedirs(self.package_folder, exist_ok=True)

        self._create_vconan_data()
        self._commonfiles_package()

        if self.datafiles.get_conf().output_type == "source-code":
            self.output.info("Packaging source code")
            self._source_code_package()

        elif self.datafiles.get_conf().output_type == "static-library":
            self.output.info("Packaging static library")
            self._static_library_package()

        elif self.datafiles.get_conf().output_type == "shared-library":
            self.output.info("Packaging shared library")
            self._shared_library_package()

        elif self.datafiles.get_conf().output_type == "executable":
            self.output.info("Packaging executable")
            self._executable_package()

        else:
            err_msg = (
                f"Unknown value for output-type: '{self.datafiles.get_conf().output_type}' "
                f"in manifest::configurations::{self.datafiles.get_conf()}"
            )
            self.output.error(err_msg)
            raise ValueError(err_msg)

        return

    # ======================================================================== #

    # IDEA: the next glob and copy functions shouldn't exist as methods inside the ConanFile
    #       (need to move them outside and find a way to make them visible everywhere in the solution)
    @staticmethod
    def _str2path(str_path: str | Path, *, verify_exists: bool = False) -> Path:
        if isinstance(str_path, str):
            str_path = Path(str_path).resolve()

        elif isinstance(str_path, Path):
            str_path = str_path.resolve()

        else:
            raise TypeError("'str_path' argument must be of type str or Path")

        if verify_exists:
            assert str_path.exists()

        return str_path

    @staticmethod
    @custom_lru_cache(maxsize=0)
    def _glob(
        pattern: str,
        root: str | Path = Path(),
        *,
        relative: bool = False,
    ) -> set[str]:
        """Find all file-paths matching the given pattern.

        e.g.:

        "src/*",  # returns all files in src folder only

        "src/*.c",  # returns all files with .c extension in src folder only

        "src/**/*",  # returns all files in src folder AND all its subfolders recursively

        "src/**",  # returns nothing. matches src folder itself and all of its subfolders recursively thus no files files are matched

        "src/*/*",  # returns all files that are exactly in one subfolder below src



        Args:
            pattern (str): A path specification of what files to match
            root (str | Path): The root path of the search. (The path to which relative paths are resolved). Defaults to Path().
            relative: bool: Whether the resulting paths are relative to the root or absolute. Defaults to False.

        Raises:
            TypeError: When root is not of type str or Path

        Returns:
            set: A set of string-paths to all files matching the pattern
        """

        # ensure root is a valid path
        root = BasicConanFile._str2path(root, verify_exists=True)

        # find all matches
        matches = {
            (
                path_match.as_posix()
                if not relative
                else path_match.relative_to(root).as_posix()
            )
            for path_match in root.glob(pattern)
            if path_match.is_file()
        }

        return matches

    @staticmethod
    def _glob_exclude(
        pattern: str,
        root: str | Path = Path(),
        *,
        exclude: str | Iterable[str] | None = None,
        relative: bool = False,
    ) -> set[str]:
        """Find all file-paths matching the given pattern.
        Excluding all file-paths matching any pattern in the exclude list.

        e.g.:

        "src/*",  # returns all files in src folder only

        "src/*.c",  # returns all files with .c extension in src folder only

        "src/**/*",  # returns all files in src folder AND all its subfolders recursively

        "src/**",  # returns nothing. matches src folder itself and all of its subfolders recursively thus no files files are matched

        "src/*/*",  # returns all files that are exactly in one subfolder below src



        Args:
            pattern (str): A path specification of what files to match
            root (str | Path): The root path of the search. (The path to which relative paths are resolved). Defaults to Path().
            exclude (str | Iterable[str]): A path specification of what files to exclude from the result. Defaults to ().
            relative: bool: Whether the resulting paths are relative to the root or absolute. Defaults to False.

        Raises:
            TypeError: When root is not of type str or Path

        Returns:
            set: A set of all files matching the pattern
        """

        # if exclude is a single string wrap it in a tuple
        if isinstance(exclude, str):
            exclude = (exclude,)

        # find all matches
        matches = BasicConanFile._glob(pattern, root, relative=relative)

        # removing excludes iteratively
        if exclude:
            for ex_pattern in exclude:
                matches.difference_update(
                    BasicConanFile._glob(
                        ex_pattern, root, relative=relative
                    )  # TODO: paralellize
                )

        return matches

    @staticmethod
    def _copyfile(
        src: str | Path,
        root: str | Path,
        dest: str | Path,
        *,
        keep_structure: bool = True,
        overwrite: bool = False,
    ) -> None:
        # ensure paths are valid
        src = BasicConanFile._str2path(src, verify_exists=True)
        root = BasicConanFile._str2path(root, verify_exists=True)
        dest = BasicConanFile._str2path(dest)

        # make sure we're copying a file
        assert src.is_file()

        # add filename if dest is a directory
        if dest.is_dir():
            dest = dest / src.name

        if keep_structure:
            # get intermediate folders between file and root
            src_rel = src.relative_to(root)

            # add intermediate folders to destination
            file_name = dest.name
            dest = dest.parent / (src_rel.parent)
            dest.mkdir(parents=True, exist_ok=True)
            dest = dest / file_name

        if not overwrite and dest.exists():
            raise FileExistsError(f"{dest} already exists")

        # copy the file
        copyfile(src=src, dst=dest)
        copystat(src=src, dst=dest)

        return

    @staticmethod
    def _copy_pattern(
        pattern: FilePatternEntry,
        root: str | Path,
        dest: str | Path,
        *,
        keep_structure: bool = True,
    ) -> None:
        root = BasicConanFile._str2path(root)
        dest = BasicConanFile._str2path(dest)

        if not root.exists():
            # self.output.warning(f"_copy_glob: root {root} does not exist.")
            return

        files_to_copy = BasicConanFile._glob_exclude(
            pattern.pattern, root, exclude=pattern.excludes
        )

        # precheck if there are matches before creating the destination directory
        if len(files_to_copy) == 0:
            return

        # make sure destination is a folder to avoid all files overwriting each other
        dest.mkdir(parents=True, exist_ok=True)
        assert dest.is_dir()

        # ensure no duplicated files within the same pattern
        # NOTE: although BasicConanFile_copyfile will raise an exception if the file already
        #       exists, it will not raise an error if the same file is being copied
        #       to the same destination over another thread
        if not keep_structure:
            duplicates = []
            files = sorted(files_to_copy, key=lambda x: Path(x).name)
            for f_name, paths in groupby(files, key=lambda x: Path(x).name):
                paths = tuple(paths)
                if len(paths) > 1:
                    # BasicConanFile.output.warning(f"Duplicate files found: {f_name}")
                    duplicates.append(paths)

            # if more than one header has the same name raise exception
            if len(duplicates):
                raise FileExistsError(f"Duplicate files found:\n{duplicates}")

        # copy the files
        with ThreadPoolExecutor() as pool:
            pool.map(
                lambda f: BasicConanFile._copyfile(
                    f, root, dest, keep_structure=keep_structure, overwrite=False
                ),
                files_to_copy,
            )

            pool.shutdown(wait=True)

        return

    @staticmethod
    def _copy_pattern_list(
        pattern_list: list[FilePatternEntry],
        root: str | Path,
        dest: str | Path,
        *,
        keep_structure: bool = True,
    ) -> None:
        root = BasicConanFile._str2path(root)
        dest = BasicConanFile._str2path(dest)

        if not root.exists():
            # BasicConanFile.output.warning(f"_copy_glob_list: root {root} does not exist.")
            return

        files_to_copy = set()
        for pattern in pattern_list:
            files_to_copy |= BasicConanFile._glob_exclude(
                pattern.pattern, root, exclude=pattern.excludes
            )

        # precheck if there are matches before creating the destination directory
        if len(files_to_copy) == 0:
            return

        # make sure destination is a folder to avoid all files overwriting each other
        dest.mkdir(parents=True, exist_ok=True)
        assert dest.is_dir()

        # ensure no duplicated files within the same pattern
        # NOTE: although BasicConanFile_copyfile will raise an exception if the file already
        #       exists, it will not raise an error if the same file is being copied
        #       to the same destination over another thread
        if not keep_structure:
            duplicates = []
            for f_name, paths in groupby(files_to_copy, key=lambda x: Path(x).name):
                paths = list(paths)
                if len(paths) > 1:
                    # BasicConanFile.output.warning(f"Duplicate files found: {f_name}")
                    duplicates.append(paths)

            # if more than one header has the same name raise exception
            if len(duplicates):
                raise FileExistsError(f"Duplicate files found:\n{duplicates}")

        # copy the files
        with ThreadPoolExecutor() as pool:
            pool.map(
                lambda f: BasicConanFile._copyfile(
                    f, root, dest, keep_structure=keep_structure, overwrite=False
                ),
                files_to_copy,
            )

            pool.shutdown(wait=True)

        return

    def _announce_method_call(self, function_name, minimal=False) -> None:
        self.output.info(f"`{function_name}` function called in: {os.getcwd()}")
        self.output.info(f"\tdirectory contents: {os.listdir()}")

        if minimal:
            return

        self.output.info(f'\tconfiguration = {self.options.get_safe("configuration")}')
        self.output.info(f'\toutput-type = {self.options.get_safe("output-type")}')

    def _set_default_option(self, option, default_value) -> None:
        if self.options.get_safe(option):
            return

        setattr(self.options, option, default_value)

    def _commonfiles_package(self) -> None:
        paths_to_copy = (
            "artifacts_paths",
            "docs_paths",
            "cfg_src_paths",
            "cfg_inc_paths_private",
            "cfg_inc_paths_public",
            "cfg_artifacts_paths",
            "shared_src_paths",
            "shared_inc_paths_private",
            "shared_inc_paths_public",
            "shared_artifacts_paths",
        )

        for path_type in paths_to_copy:
            dest_rel = paths_dst_mapping[path_type]
            dest = os.path.join(self.package_folder, *dest_rel)

            self._copy_pattern_list(
                getattr(self.datafiles.get_conf(), path_type),
                self.source_folder,
                dest,
                keep_structure=True,
            )

    def _source_code_package(self) -> None:
        paths_to_copy = (
            "src_paths",
            "inc_paths_private",
            "inc_paths_public",
            "lib_paths",
            "assembly_paths",
        )

        for path_type in paths_to_copy:
            dest_rel = paths_dst_mapping[path_type]
            dest = os.path.join(self.package_folder, *dest_rel)

            self._copy_pattern_list(
                getattr(self.datafiles.get_conf(), path_type),
                self.source_folder,
                dest,
                keep_structure=False,
            )

    def _static_library_package(self) -> None:
        self.run(
            f'cmake --install "{self.build_folder}" --prefix "{self.folders.package_folder}"',
            cwd=self.build_folder,
        )

    def _shared_library_package(self) -> None:
        self.run(
            f'cmake --install "{self.build_folder}" --prefix "{self.folders.package_folder}"',
            cwd=self.build_folder,
        )

    def _executable_package(self) -> None:
        self.run(
            f'cmake --install "{self.build_folder}" --prefix "{self.folders.package_folder}"',
            cwd=self.build_folder,
        )

    def _create_vconan_data(self) -> None:
        # save original paths for files
        # TODO: refactor this mess
        package_data_file_contents = {
            "vconan_version": "1.0.0",
            "original_paths": [],
        }
        for path_type, base_dest in paths_dst_mapping.items():
            pattern_list = getattr(self.datafiles.get_conf(), path_type)

            # RFE: refator different types of paths into global variables?
            if path_type not in (
                "artifacts_paths",
                "docs_paths",
                "cfg_src_paths",
                "cfg_inc_paths_private",
                "cfg_inc_paths_public",
                "cfg_artifacts_paths",
                "shared_src_paths",
                "shared_inc_paths_private",
                "shared_inc_paths_public",
                "shared_artifacts_paths",
            ):
                get_dst = lambda f_rel: "/".join(base_dest + [Path(f_rel).name])
            else:
                get_dst = lambda f_rel: "/".join(base_dest + [f_rel])

            for pattern in pattern_list:
                for file_rel in self._glob_exclude(
                    pattern.pattern,
                    self.source_folder,
                    exclude=pattern.excludes,
                    relative=True,
                ):
                    file_rel = file_rel.replace("\\", "/")
                    dest_rel = get_dst(file_rel)

                    with open(os.path.join(self.source_folder, file_rel), "rb") as f:
                        file_digest = hashlib.file_digest(f, "SHA-256")

                    file_digest.update(file_rel.encode())
                    # file_digest.update(dest_rel)

                    package_data_file_contents["original_paths"].append(
                        {
                            "pkg_folder": dest_rel,
                            "project_folder": file_rel,
                            "hash": file_digest.hexdigest(),
                        }
                    )

        with open(os.path.join(self.package_folder, PACKAGE_DATA_FILE_NAME), "w") as f:
            # json.dump(package_data_file_contents, f, indent=2)
            json.dump(package_data_file_contents, f)

        return


# fmt: off
paths_dst_mapping = {
    "src_paths"                 : ["src"],
    "inc_paths_private"         : ["src"],
    "inc_paths_public"          : ["include"],
    "lib_paths"                 : ["lib"],
    "assembly_paths"            : ["asm"],
    "artifacts_paths"           : ["artifacts"],
    "docs_paths"                : ["docs"],
    "cfg_src_paths"             : [".valeo-project-cfg", "src"],
    "cfg_inc_paths_private"     : [".valeo-project-cfg", "src"],
    "cfg_inc_paths_public"      : [".valeo-project-cfg", "include"],
    "cfg_artifacts_paths"       : [".valeo-project-cfg", "artifacts"],
    "shared_src_paths"          : [".valeo-project-shared", "src"],
    "shared_inc_paths_private"  : [".valeo-project-shared", "src"],
    "shared_inc_paths_public"   : [".valeo-project-shared", "include"],
    "shared_artifacts_paths"    : [".valeo-project-shared", "artifacts"],
}
# fmt: on
