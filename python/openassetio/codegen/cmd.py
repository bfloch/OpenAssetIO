import argparse
import inspect
import os

import jinja2
import yaml


def genPython(inputYamlFilePath, outputDirPath, isDryRun, isVerbose):
    # TODO(DF): Use pkg_resources et al.
    templateDir = os.getenv("OPENASSETIO_TEMPLATE_DIR")
    assert templateDir

    env = jinja2.Environment(loader=jinja2.FileSystemLoader(templateDir))
    tmpl = env.get_template(os.path.join("python", "trait.pyi"))

    with open(inputYamlFilePath) as f:
        model = yaml.load(f)

    # TODO(DF): Convert types to language-specific strings (e.g.
    #  "string" -> "str")

    output = tmpl.render(model)

    packageDirPath = os.path.join(outputDirPath, model["package"])

    os.makedirs(packageDirPath, exist_ok=True)

    # TODO(DF): Gather traits by usage

    with open(os.path.join(packageDirPath, "__init__.py"), "w") as f:
        f.write(output)


def main():
    cmdline = argparse.ArgumentParser(
        prog="openassetio-codegen",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        description=inspect.cleandoc(
            """
            The openassio-codegen utility generates code that provides
            strongly-typed views on an openassetio traits data instance. The
            tool is capable of generating code in a number of languages from the
            supplied file, containing the simplified declaration of one or more
            traits or specifications using the OpenAssetIO traits and
            specification declaration schema.

            By default, code is generated for all supported unless one or more
            language flags are specifed.
            """))

    cmdline.add_argument(
        "-d", "--dry-run", action="store_true",
        help="Load and verify the supplied declarations without generating any code")

    cmdline.add_argument(
        "-i", "--input-yaml", required=True,
        help="YAML file detailing traits to generate")

    cmdline.add_argument(
        "-o", "--output-dir", required=True,
        help="Generate code under the supplied directory, the utility will attempt to created this"
             " directory if it does not exist")

    cmdline.add_argument("--python", action="store_true", help="Generate Python classes")

    cmdline.add_argument("-v", "--verbose", action="store_true",
        help="Prints a description of the traits and specifications to stderr, and the path to"
             " each file generated file to stdout.")

    args = cmdline.parse_args()

    genPython(args.input_yaml, args.output_dir, args.dry_run, args.verbose)
