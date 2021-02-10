# Compiler Passes and What They Do

So we got a list of micro-passes that do a small job on the AST,
such as collecting, inferring and mutating the compiler state depending on what
they are designed for.

A complete list is presented here:

- `DesugarVisitor`
	- This is where we added things like implicit returns and resolve pipe operators.

- `StructVisitor`
	- This collects struct names declared and also creates types for them.

- `StructFieldVisitor`
	- This collects information about structs' fields whom were collected in `StructVisitor`.
	- Also creates & adds those field types to respective structs.

- `FnAndMethodVisitor`
	- This collects method & function names and also creates types for them.

- `SymVisitor`
	- This identifies symbols defined in methods/functions.
