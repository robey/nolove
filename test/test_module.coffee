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

describe "Function", ->
  context = llvm.getGlobalContext()
  module = context.newModule("mymod")
  double = context.getDoubleType()

  it "can get/set a name", ->
    ftype = llvm.getFunctionType(double, [ double ], false)
    f = module.newFunction(ftype, llvm.Linkage.ExternalLinkage, "half")
    f.hasName().should.equal(true)
    f.getName().should.eql("half")
    f.setName("halfsies")
    f.getName().should.eql("halfsies")
    f.toString().should.eql("<Value \ndeclare double @halfsies(double)\n>")

  it "has arguments", ->
    ftype = llvm.getFunctionType(double, [ double ], false)
    f = module.newFunction(ftype, llvm.Linkage.ExternalLinkage, "half")
    f.arguments().length.should.eql(1)
    f.arguments()[0].hasName().should.equal(false)
    f.arguments()[0].setName("n")
    f.arguments()[0].hasName().should.equal(true)
    f.arguments()[0].getName().should.eql("n")
    f.arguments()[0].getType().toString().should.eql("<Type double>")

describe "Constant", ->
  context = llvm.getGlobalContext()
  
  it "can be 0.0", ->
    n = context.getFP(0.0)
    n.isZero().should.equal(true)
    n.isNullValue().should.equal(true) # ???
    n.isExactlyValue(0.0).should.equal(true)
    n.isExactlyValue(0.5).should.equal(false)

  it "can be 0.5", ->
    n = context.getFP(0.5)
    n.isZero().should.equal(false)
    n.isNullValue().should.equal(false)
    n.isExactlyValue(0.0).should.equal(false)
    n.isExactlyValue(0.5).should.equal(true)

describe "IRBuilder", ->
  context = llvm.getGlobalContext()
  module = context.newModule("mymod")
  builder = context.newIRBuilder()
  double = context.getDoubleType()

  it "can multiply", ->
    two = context.getFP(2.0)
    op = builder.createFMul(two, two, "2x2")
    op.getType().toString().should.equal("<Type double>")

  it "can make a doubler function", ->
    ftype = llvm.getFunctionType(double, [ double ], false)
    f = module.newFunction(ftype, llvm.Linkage.ExternalLinkage, "twice")
    f.arguments()[0].setName("n")
    two = context.getFP(2.0)
    op = builder.createFMul(f.arguments()[0], two, "times2")
    op.toString().should.equal("<Value   %times2 = fmul double %n, 2.000000e+00>")

describe "complete Function with code", ->
  context = llvm.getGlobalContext()
  builder = context.newIRBuilder()
  double = context.getDoubleType()

  buildFunction = ->
    module = context.newModule("mymod")
    ftype = llvm.getFunctionType(double, [ double ], false)
    f = module.newFunction(ftype, llvm.Linkage.ExternalLinkage, "twice")
    f.arguments()[0].setName("n")
    block = context.newBasicBlock("entry", f)
    builder.setInsertPoint(block)
    op = builder.createFMul(f.arguments()[0], context.getFP(2.0), "times2")
    builder.createRet(op)
    [ module, f ]

  it "can verify", ->
    [ module, f ] = buildFunction()
    f.verify()
    console.log "\n\n"
    module.dump()
    console.log "\n\n"

  it "can compile", ->
    [ module, f ] = buildFunction()
    engine = module.newExecutionEngine()
#    console.log 
    engine.getTargetData()

