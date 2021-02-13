# Compiler Passes and What They Do

So we got a list of micro-passes that do a small job on the AST,
such as collecting, inferring and mutating the compiler state depending on what
they are designed for.

A complete list is presented here:

- `DesugarVisitor`
	- This is where we added things like implicit returns and resolve pipe operators.
	- Plus, it also adds unstated types as `T_NONE` which comes in handy when verifying types.

- `InferVisitor`
	- This is a non-context-aware type infering pass, very dumb but effective.
	- Main goal is to make things easier for the more sophisticated type infering pass.
