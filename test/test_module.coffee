should = require 'should'
llvm = require '../build/Release/llvm'

describe "Module", ->
  it "has a name", ->
    m = llvm.getGlobalContext().newModule("hullo")
    m.getModuleIdentifier().should.equal("hullo")
