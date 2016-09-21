# API-scan

API-scan is a command-line utility that can analyze C source code and output a list of exported functions as XML. Such 
data can be used to generate bindings in other programming languages.

In addition, conversion dictionaries can be provided as arguments to automatically translate type-names or argument 
names.

## Usage

```

   api-scan  [-o <string>] [-f <string>] [-p <string>] [-t <string>] [--]
             [--version] [-h] <string> ...


Where:

   -o <string>,  --out-format <string>
     Output format - xml/json

   -f <string>,  --field-dict <string>
     File containing translations for struct field names

   -p <string>,  --param-dict <string>
     File containing translations for parameter names

   -t <string>,  --type-dict <string>
     File containing translations for function types

   --,  --ignore_rest
     Ignores the rest of the labeled arguments following this flag.

   --version
     Displays version information and exits.

   -h,  --help
     Displays usage information and exits.

   <string>  (accepted multiple times)
     (required)  Source files to scan


   Scans C code/header files for exposed functions and structs, and returns
   function and type information as XML or JSON.

```

## Project status

This utility was designed to scan exported methods in [libsodium](https://github.com/jedisct1/libsodium). At the 
moment that is also the only project on which this utility was tested.

## Docker image

```docker
FROM 1of0/api-scan

# ...

ENTRYPOINT api-scan /path/to/your/sourcefiles
``` 

## Todo

- [x] Support for struct
- [x] Add JSON output formatter
- [x] Support for `#define`s
- [ ] C API
- [ ] Support for enums
- [ ] More input validation (file exists, etc.)
- [ ] Un-break multi-file scanning
- [ ] Test with other libraries
- [ ] Support for consts
- [ ] Improve escaping in formatter
