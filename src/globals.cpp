#include "globals.h"

using namespace v8;

template <typename T, typename Wrapped>
void LLinkage::init(NodeProto<T, Wrapped> proto) {
  proto.addField("ExternalLinkage", Integer::New(llvm::GlobalValue::ExternalLinkage));
  proto.addField("AvailableExternallyLinkage", Integer::New(llvm::GlobalValue::AvailableExternallyLinkage));
  proto.addField("LinkOnceAnyLinkage", Integer::New(llvm::GlobalValue::LinkOnceAnyLinkage));
  proto.addField("LinkOnceODRLinkage", Integer::New(llvm::GlobalValue::LinkOnceODRLinkage));
  proto.addField("WeakAnyLinkage", Integer::New(llvm::GlobalValue::WeakAnyLinkage));
  proto.addField("WeakODRLinkage", Integer::New(llvm::GlobalValue::WeakODRLinkage));
  proto.addField("AppendingLinkage", Integer::New(llvm::GlobalValue::AppendingLinkage));
  proto.addField("InternalLinkage", Integer::New(llvm::GlobalValue::InternalLinkage));
  proto.addField("PrivateLinkage", Integer::New(llvm::GlobalValue::PrivateLinkage));
  proto.addField("LinkerPrivateLinkage", Integer::New(llvm::GlobalValue::LinkerPrivateLinkage));
  proto.addField("LinkerPrivateWeakLinkage", Integer::New(llvm::GlobalValue::LinkerPrivateWeakLinkage));
  proto.addField("LinkerPrivateWeakDefAutoLinkage", Integer::New(llvm::GlobalValue::LinkerPrivateWeakDefAutoLinkage));
  proto.addField("DLLImportLinkage", Integer::New(llvm::GlobalValue::DLLImportLinkage));
  proto.addField("DLLExportLinkage", Integer::New(llvm::GlobalValue::DLLExportLinkage));
  proto.addField("ExternalWeakLinkage", Integer::New(llvm::GlobalValue::ExternalWeakLinkage));
  proto.addField("CommonLinkage", Integer::New(llvm::GlobalValue::CommonLinkage));
}
