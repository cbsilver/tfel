The `@MaximumNumberOfSubSteps` keyword let the user specify the
maximum number of sub steps allowed.

This keyword is followed by an integer.

When the global algorithm fails to reach equilibrium (see the
`@MaximumNumberOfIterations` keyword), the time step can be divided by
two. The maximal number of times the time step is reduced if given by
maximum number of sub steps.

## Example

~~~~ {.cpp}
@MaximumNumberOfSubSteps 10;
~~~~~~~~
