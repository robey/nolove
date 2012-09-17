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
    ft.isVarArg().should.equal(false)
    ft.getNumParams().should.equal(1)
    x = ft.getParamType(0)
    x.isDoubleType().should.equal(true)
    ft.toString().should.eql("<Type double (double)>")

describe "Module", ->
  it "has a name", ->
    m = llvm.getGlobalContext().newModule("hullo")
    m.getModuleIdentifier().should.equal("hullo")

describe "function", ->
  context = llvm.getGlobalContext()
  module = context.newModule("mymod")

  it "can get/set a name", ->
    d = context.getDoubleType()
    ftype = llvm.getFunctionType(d, [ d ], false)
    f = module.newFunction(ftype, llvm.Linkage.ExternalLinkage, "half")
    f.hasName().should.equal(true)
    f.getName().should.eql("half")
    f.setName("halfsies")
    f.getName().should.eql("halfsies")
    f.toString().should.eql("<Value \ndeclare double @halfsies(double)\n>")
