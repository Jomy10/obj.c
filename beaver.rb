Project(name: "obj.c")

C::Library(
  name: "obj",
  sources: "src/impl.c",
  include: ["include", "deps/metalang99/include"],
  artifacts: [:staticlib, :dynlib]
)
