The `@StiffnessMatrixType` keyword let the user specifiy choose type
of stiffness matrix that shall be given by the mechanical behaviour
and that will be used by the resolution algorithm.

This keyword is followed by a string. The following values are
allowed:

- Elastic (undammaged)
- SecantOperator (damaged)
- TangentOperator
- ConsistentTangentOperator

## Example

~~~~ {.cpp}
@StiffnessMatrixType 'Elastic';
~~~~~~~~


