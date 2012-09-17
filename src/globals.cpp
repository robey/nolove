#include "globals.h"

using namespace v8;

void LLinkage::init(Handle<Object> obj) {
  addObjectField(obj, "ExternalLinkage", Integer::New(llvm::GlobalValue::ExternalLinkage));
  addObjectField(obj, "AvailableExternallyLinkage", Integer::New(llvm::GlobalValue::AvailableExternallyLinkage));
  addObjectField(obj, "LinkOnceAnyLinkage", Integer::New(llvm::GlobalValue::LinkOnceAnyLinkage));
  addObjectField(obj, "LinkOnceODRLinkage", Integer::New(llvm::GlobalValue::LinkOnceODRLinkage));
  addObjectField(obj, "WeakAnyLinkage", Integer::New(llvm::GlobalValue::WeakAnyLinkage));
  addObjectField(obj, "WeakODRLinkage", Integer::New(llvm::GlobalValue::WeakODRLinkage));
  addObjectField(obj, "AppendingLinkage", Integer::New(llvm::GlobalValue::AppendingLinkage));
  addObjectField(obj, "InternalLinkage", Integer::New(llvm::GlobalValue::InternalLinkage));
  addObjectField(obj, "PrivateLinkage", Integer::New(llvm::GlobalValue::PrivateLinkage));
  addObjectField(obj, "LinkerPrivateLinkage", Integer::New(llvm::GlobalValue::LinkerPrivateLinkage));
  addObjectField(obj, "LinkerPrivateWeakLinkage", Integer::New(llvm::GlobalValue::LinkerPrivateWeakLinkage));
  addObjectField(obj, "LinkerPrivateWeakDefAutoLinkage", Integer::New(llvm::GlobalValue::LinkerPrivateWeakDefAutoLinkage));
  addObjectField(obj, "DLLImportLinkage", Integer::New(llvm::GlobalValue::DLLImportLinkage));
  addObjectField(obj, "DLLExportLinkage", Integer::New(llvm::GlobalValue::DLLExportLinkage));
  addObjectField(obj, "ExternalWeakLinkage", Integer::New(llvm::GlobalValue::ExternalWeakLinkage));
  addObjectField(obj, "CommonLinkage", Integer::New(llvm::GlobalValue::CommonLinkage));
}
