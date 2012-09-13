should = require 'should'
llvm = require '../build/Release/llvm'

describe "Context", ->
  context = llvm.getGlobalContext()

  it "makes a double type", ->
    d = context.getDoubleType()
    d.isDoubleType().should.equal(true)

  it "makes a function type for double -> double", ->
    d = context.getDoubleType()
    ft = llvm.getFunctionType(d, [ d ], false)
    ft.isFunctionType().should.equal(true)
    ft.isFunctionVarArg().should.equal(false)
    ft.getFunctionNumParams().should.equal(1)
    x = ft.getFunctionParamType(0)
    x.isDoubleType().should.equal(true)

describe "Module", ->
  it "has a name", ->
    m = llvm.getGlobalContext().newModule("hullo")
    m.getModuleIdentifier().should.equal("hullo")
