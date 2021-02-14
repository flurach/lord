# Compiler Passes and What They Do

So we got a list of micro-passes that do a small job on the AST,
such as collecting, inferring and mutating the compiler state depending on what
they are designed for.

A complete list is presented here:

- `DesugarVisitor`
	- This is where we added things like implicit returns and resolve pipe operators.
	- Plus, it also adds unstated types as `T_NONE` which comes in handy when verifying types.

- WIP `ToplevelCheckVisitor`
	- Checks top level code. Only functions are allowed! (for now)

- WIP `ParseCheckVisitor`
	- Checks if the input is parsed correctly. Throws error if not.

- `PreInferVisitor`
	- This is a non-context-aware type infering pass, very dumb but effective.
	- Main goal is to make things easier for the more sophisticated type infering pass.

- WIP `CallVisitor`
	- Collects function calls with their arguments to later aid with type inference.
