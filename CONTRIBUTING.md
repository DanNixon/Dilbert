# Contributing

- Keep pull requests limited to a single thing (fixing an issue in an existing
  app, adding a new app, or fixing an issue in the library)

## Coding standards

- Keep clang-format happy
- Member variables are prefixed with `m_`
- Global variables are prefixed with `g_`
- The order of declaration in class headers is (each of which should be in their
  own scope region, i.e. don't mix private variables and functions):
 - public constants
 - public functions
 - protected functions
 - private functions
 - protected variables
 - private variables
