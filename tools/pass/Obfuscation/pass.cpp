#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/CFG.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstrTypes.h"
#include <random>

#define OPEN_SYMBOLIC_MEMORY_SNIPPET 1
#define OPEN_FACTOR_OPAQUE_PREDICATE 1
#define OPEN_CRYPTO_OPAQUE_PREDICATE 1
#define OPEN_LOOP_OPAQUE_PREDICATE 1

#define OPEN_MEMORY_DETAINT 1
#define OPEN_OPAQUE_CONST_DETAINT 1

#define EACH_BLOCK_ONLY_ONE_OBFS 1

using namespace llvm;

const uint32_t primerNumber[] = {2147483659, 2147483693, 2147483713, 2147483743, 2147483777,
                                 2147483783, 2147483813, 2147483857, 2147483867, 2147483869,
                                 2117483651, 2117483659, 2117483677, 2117483717, 2117483741,
                                 2117483759, 2117483783, 2117483821, 2117483831, 2117483833
};

static void getPrimeNumber(uint32_t *p1, uint32_t *p2) {
    *p1 = primerNumber[rand() % sizeof(primerNumber)];
    for (int i = 0; i < sizeof(primerNumber); i++) {
        if (primerNumber[i] % 10 != *p1 % 10) {
            *p2 = primerNumber[i];
            return;
        }
    }
    *p2 = *p1;
}

static void hex2i64(uint8_t *hex, uint32_t size, uint64_t *i64_arr) {
    for (int i = 0; i < size; i += 8) {
        i64_arr[i / 8] = *((uint64_t *)(hex + i));
    }
}

namespace {
    struct Obfuscation : public FunctionPass {
        static char ID;

        Obfuscation() : FunctionPass(ID) {}

        void insertFactorOP(Function &F) {
            for (BasicBlock &BB: F) {
                for (Instruction &I: BB) {
                    //if the inst is icmp

                    if (I.getOpcode() == Instruction::ICmp) {

                        //errs() << I << "\n";

                        auto *cmp = dyn_cast<ICmpInst>(&I);
                        if (cmp == NULL) {
                            continue;
                        }
                        //we obfuscate eq/ne cmp inst only
                        if (cmp->getPredicate() == ICmpInst::ICMP_EQ ||
                            cmp->getPredicate() == ICmpInst::ICMP_NE) {
                            ConstantInt *v = NULL;
                            Value *cmp_var = NULL;
                            int count = 0;
                            int index_of_const = -1;
                            int index_of_var = -1;
                            for (int i = 0; i < cmp->getNumOperands(); i++) {
                                if (isa<ConstantInt>(cmp->getOperand(i))) {
                                    v = dyn_cast<ConstantInt>(cmp->getOperand(i));
                                    count++;
                                    index_of_const = i;
                                } else {
                                    cmp_var = cmp->getOperand(i);
                                    index_of_var = i;
                                }
                            }

                            //errs() << count << " " << index_of_var << " " << index_of_const << "\n";

                            //if 2 operands are both const int, search next inst
                            if (count == 2) {
                                continue;
                            }

                            //no const operand in the cmp inst, search next inst
                            if (v == NULL || cmp_var == NULL) {
                                continue;
                            }

                            if (v->getBitWidth() != 32 && v->getBitWidth() != 64) {
                                continue;
                            }

                            uint32_t p1, p2;
                            getPrimeNumber(&p1, &p2);
                            uint64_t mul = p1 * p2;
                            ConstantInt *mul_result = ConstantInt::get(Type::getInt64Ty(F.getContext()),
                                                                       uint64_t(p1) * uint64_t(p2));

                            uint64_t cmp_const = v->getZExtValue();
                            IRBuilder<> builder(cmp);

                            if (v->getBitWidth() == 32) {
                                //cmp_var = cmp_var + (p1 - cmp_const)
                                cmp_var = builder.CreateAdd(cmp_var, ConstantInt::get(
                                        Type::getInt32Ty(F.getContext()), p1 - uint32_t(cmp_const)));
                                //if cmp_var equals 0, we should set cmp_var a random even number, because x % 0 will cause
                                // a divided-by-zero exception
                                //cmp_var = select(cmp_var == 0, (rand() + 12) & 1, cmp_var)
                                cmp_var = builder.CreateSelect(builder.CreateICmpEQ(cmp_var, ConstantInt::get(Type::getInt32Ty(F.getContext()), 0)),
                                                               ConstantInt::get(Type::getInt32Ty(F.getContext()), (rand() + 12) & 1),
                                                               cmp_var);
                                //zext cmp_var to 64 bits
                                cmp_var = builder.CreateZExt(cmp_var, Type::getInt64Ty(F.getContext()));
                                //rem1 = p1 * p2 % cmp_var
                                Value *rem1 = builder.CreateURem(mul_result, cmp_var);
                                //rem2 = cmp_var % 10
                                Value *rem2 = builder.CreateURem(
                                        cmp_var, ConstantInt::get(Type::getInt64Ty(F.getContext()), 10));

                                //if rem1 == 0, then cmp_var == p1 or p2
                                //so, we should check rem2 to distinguish p1 and p2

                                Value *bool1 = builder.CreateICmpEQ(rem1, ConstantInt::get(
                                        Type::getInt64Ty(F.getContext()), 0));
                                Value *bool2 = builder.CreateICmpNE(rem1, ConstantInt::get(
                                        Type::getInt64Ty(F.getContext()), p2 % 10));
                                //bool3 = p1 * p2 % cmp_var == 0 && cmp_var % 10 != p2 % 10
                                Value *bool3 = builder.CreateAnd(bool1, bool2);
                                //bool3 = bool3 & cmp_var != 1
                                bool3 = builder.CreateAnd(bool3, builder.CreateICmpNE(cmp_var, ConstantInt::get(
                                        Type::getInt64Ty(F.getContext()), 1)));
                                //cmp x, const => cmp bool3,1
                                cmp->setOperand(index_of_var, bool3);
                                cmp->setOperand(index_of_const, ConstantInt::get(Type::getInt1Ty(F.getContext()), 1));
                            } else {
                                //lo = low32(cmp_var), hi = high32(cmp_var)
                                Value *lo = builder.CreateTrunc(cmp_var, Type::getInt32Ty(F.getContext()));
                                Value *hi = builder.CreateTrunc(builder.CreateLShr(cmp_var, 32), Type::getInt32Ty(F.getContext()));

                                lo = builder.CreateAdd(lo, ConstantInt::get(Type::getInt32Ty(F.getContext()),
                                                                            p1 - uint32_t(cmp_const)));
                                hi = builder.CreateAdd(hi, ConstantInt::get(Type::getInt32Ty(F.getContext()),
                                                                            p2 - uint32_t((cmp_const >> 32))));
                                lo = builder.CreateZExt(lo, Type::getInt64Ty(F.getContext()));
                                hi = builder.CreateZExt(hi, Type::getInt64Ty(F.getContext()));
                                //mul = (lo + p1 - low32(cmp_const)) * (hi + p2 - high32(cmp_const))
                                Value *mul = builder.CreateMul(lo, hi);
                                Value *bool1 = builder.CreateICmpEQ(mul, mul_result);
                                bool1 = builder.CreateAnd(bool1, builder.CreateAnd(builder.CreateICmpNE(lo,
                                                                                                        ConstantInt::get(
                                                                                                                Type::getInt64Ty(
                                                                                                                        F.getContext()),
                                                                                                                1)),
                                                                                   builder.CreateICmpNE(hi,
                                                                                                        ConstantInt::get(
                                                                                                                Type::getInt64Ty(
                                                                                                                        F.getContext()),
                                                                                                                1))));
                                cmp->setOperand(index_of_var, bool1);
                                cmp->setOperand(index_of_const, ConstantInt::get(Type::getInt1Ty(F.getContext()), 1));
                            }
                            break; //next BB
                        }
                    }
                }
            }
        }

        void insertCryptoOP(Function &F) {

        }

        void insertLoopOP(Function &F) {
            for (BasicBlock &BB: F) {
                for (Instruction &I: BB) {
                    if (I.getOpcode() != Instruction::ICmp) {
                        continue;
                    }

                    ICmpInst *cmp = dyn_cast<ICmpInst>(&I);
                    if (cmp == NULL) {
                        continue;
                    }

                    Value *const_op = NULL;
                    Value *int_op = NULL;
                    int const_op_i = -1;
                    int int_op_i = -1;
                    for (int i = 0; i < 2; i++) {
                        if (cmp->getOperand(i)->getType()->isIntegerTy(32) || cmp->getOperand(i)->getType()->isIntegerTy(64)) {
                            if (isa<ConstantInt>(cmp->getOperand(i))) {
                                const_op = cmp->getOperand(i);
                                const_op_i = i;
                            }
                            else {
                                int_op = cmp->getOperand(i);
                                int_op_i = i;
                            }
                        }
                    }

                    if (const_op == NULL || int_op == NULL) {
                        continue;
                    }

                    int64_t wanna;
                    if (cmp->isSigned()) {
                        wanna = dyn_cast<ConstantInt>(const_op)->getSExtValue();
                    }
                    else {
                        wanna = dyn_cast<ConstantInt>(const_op)->getZExtValue();
                    }
                    if (wanna < 0 || wanna > 0x7FFFFFFF) {
                        continue;
                    }
                    Value *addr = insertLoopConst(int_op, cmp, wanna);
                    /*
                    std::vector<BasicBlock *> invalid;
                    for (BasicBlock &bb: F) {
                        if (bb.getSinglePredecessor() == NULL) {
                            invalid.push_back(&bb);
                        }
                    }
                    for (int i = 0; i < invalid.size(); i++) {
                        invalid[i]->eraseFromParent();
                    }
                    */
                    IRBuilder<> ir(cmp);
                    Value *op_const = ir.CreateLoad(addr);
                    if (const_op->getType()->isIntegerTy(32)) {
                        op_const = ir.CreateTrunc(op_const, ir.getInt32Ty());
                    }
                    cmp->setOperand(const_op_i, op_const);

                    std::vector<BasicBlock *> invalid;
                    for (BasicBlock &bb: F) {
                        if (pred_empty(&bb) && succ_empty(&bb) && bb.getInstList().empty()) {
                            invalid.push_back(&bb);
                        }
                    }
                    for (int i = 0; i < invalid.size(); i++) {
                        invalid[i]->eraseFromParent();
                    }

                    return;
                }
            }
        }

        //insert a Loop-based op const before ins
        //the input LLVM Value of inserted loop is v
        //return the LLVM Value PTR to the generated op const
        Value *insertLoopConst(Value *v, Instruction *ins, int64_t wanna) {
            //the v must be int32 or int64 type
            if (! (v->getType()->isIntegerTy(32) || v->getType()->isIntegerTy(64))) {
                return NULL;
            }

            BasicBlock *BB = ins->getParent();
            Function *F = BB->getParent();
            BasicBlock *succBB = BB->splitBasicBlock(ins);

            //now, we need to insert a while loop
            BasicBlock *loop_body = BasicBlock::Create(F->getContext(), "op_loop_body", F);
            //IRBuilder<> loop_body_ir(loop_body);
            BasicBlock *loop_entry = BasicBlock::Create(F->getContext(), "op_loop_entry", F);
            IRBuilder<> loop_entry_ir(loop_entry);

            //errs() << *BB->getTerminator();
            BB->getTerminator()->setOperand(0, loop_entry);
            IRBuilder<> BB_ir(BB->getTerminator());
            if (v->getType()->isIntegerTy(32)) {
                v = BB_ir.CreateZExt(v, BB_ir.getInt64Ty());
            }
            v = BB_ir.CreateAdd(v, BB_ir.getInt64(uint32_t(rand()) + 0x7FFFFF + wanna));
            Value *loop_var_addr = BB_ir.CreateAlloca(BB_ir.getInt64Ty());
            BB_ir.CreateStore(v, loop_var_addr);

            loop_entry_ir.CreateCondBr(loop_entry_ir.CreateICmpSGT(loop_entry_ir.CreateLoad(loop_var_addr), loop_entry_ir.getInt64(wanna))
                                       , loop_body, succBB);

            static uint32_t prime_number[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 31};
            BasicBlock *if_branch[10];
            BasicBlock *if_body[10];
            for (int i = 0; i < 10; i++) {
                if_branch[i] = BasicBlock::Create(F->getContext(), "op_if_branch", F);
                if_body[i] = BasicBlock::Create(F->getContext(), "op_if_body", F);
            }
            if_branch[0] = loop_body;

            int i;

            for (i = 0; i < 3; i++) {
                int r = rand() % int32_t(sizeof(prime_number) / sizeof(prime_number[0]));
                IRBuilder<> branch_ir(if_branch[i]);
                Value *loop_value = branch_ir.CreateLoad(loop_var_addr);
                Value *cond1 = branch_ir.CreateICmpSGT(loop_value, branch_ir.getInt64(prime_number[r] * wanna + rand() % 10 + 1));
                Value *rem = branch_ir.CreateSRem(loop_value, branch_ir.getInt64(prime_number[r]));
                Value *cond2;
                if (rand() % 2) {
                    cond2  = branch_ir.CreateICmpNE(rem, branch_ir.getInt64(0));
                }
                else {
                    cond2 = branch_ir.CreateICmpEQ(rem, branch_ir.getInt64(0));
                }
                Value *cond = branch_ir.CreateAnd(cond1, cond2);
                branch_ir.CreateCondBr(cond, if_body[i], if_branch[i + 1]);

                IRBuilder<> body_ir(if_body[i]);
                loop_value = body_ir.CreateLoad(loop_var_addr);
                if (rand() % 2) {
                    loop_value = body_ir.CreateSDiv(loop_value, body_ir.getInt64(prime_number[r]));
                }
                else {
                    loop_value = body_ir.CreateMul(loop_value, body_ir.getInt64(0xFFFFFFFFU / prime_number[r]));
                    loop_value = body_ir.CreateLShr(loop_value, body_ir.getInt64(32));
                }
                body_ir.CreateStore(loop_value, loop_var_addr);
                body_ir.CreateBr(loop_entry);
            }

            IRBuilder<> else_ir(if_branch[i]);
            else_ir.CreateStore(else_ir.CreateSub(else_ir.CreateLoad(loop_var_addr), else_ir.getInt64(1)), loop_var_addr);
            else_ir.CreateBr(loop_entry);
            return loop_var_addr;
        }

        void insertMemoryAttackTaint(Function &F) {

        }

        void insertOPConstAttackTaint(Function &F) {

        }

        void insertSymbolicMemorySnippet(Function &F) {
            BasicBlock &entryBB = F.getEntryBlock();
            IRBuilder<> builder(entryBB.getFirstNonPHIOrDbgOrLifetime());
            Value *array = builder.CreateAlloca(ArrayType::get(Type::getInt8Ty(F.getContext()), 256));

            //initialize the array
            //array[i] = i

            Value *i64_ptr = builder.CreateBitCast(array, PointerType::get(ArrayType::get(builder.getInt64Ty(), 32),
                                                                           dyn_cast<PointerType>(array->getType())->getAddressSpace()));

            uint64_t i64_arr[256 / 8];
            uint8_t buf[256];
            for (int i = 0; i < 256; i++) {
                buf[i] = uint8_t(i);
            }
            hex2i64(buf, 256, i64_arr);
            for (int i = 0; i < (256 / 8); i++) {
                builder.CreateStore(builder.getInt64(i64_arr[i]),
                                    builder.CreateConstGEP2_64(i64_ptr, 0, i));
            }


            for (BasicBlock &BB: F) {
                if (&BB == &entryBB) {
                    continue;
                }

                auto iter = BB.begin();
                while (iter != BB.end()) {
                    Instruction &I = *iter;
                    for (int i = 0; i < I.getNumOperands(); i++) {
                        Value *v = I.getOperand(i);

                        int len_of_bytes;
                        if (v->getType()->isIntegerTy(32)) {
                            len_of_bytes = 4;
                        }
                        else if (v->getType()->isIntegerTy(64)) {
                            len_of_bytes = 8;
                        }
                        else {
                            continue;
                        }
                        if (isa<ConstantInt>(v)) {
                            continue;
                        }

                        IRBuilder<> builder(&I);
                        Value *bytes[8] = {NULL};
                        Value *magic_ff;
                        Value *magic_0;
                        IntegerType *num_ty;
                        if (len_of_bytes == 4) {
                            magic_ff = builder.getInt32(0xFF);
                            magic_0 = builder.getInt32(0);
                            num_ty = builder.getInt32Ty();
                        }
                        else {
                            magic_ff = builder.getInt64(0xFF);
                            magic_0 = builder.getInt64(0);
                            num_ty = builder.getInt64Ty();
                        }

                        bytes[0] = builder.CreateAnd(v, magic_ff);

                        for (int j = 1; j < len_of_bytes; j++) {
                            bytes[j] = builder.CreateAnd(builder.CreateLShr(v, j * 8), magic_ff);
                        }

                        //bytes[i] = array[bytes[i]]
                        for (int j = 0; j < len_of_bytes; j++) {
                            Value *idx[2] = {magic_0, bytes[j]};
                            bytes[j] = builder.CreateZExt(builder.CreateLoad(builder.CreateGEP(array, idx)), num_ty);
                        }

                        //bytes[0] = bytes[0] | bytes[1] << 8 | bytes[2] << 16 | bytes[3] << 24
                        for (int j = 1; j < len_of_bytes; j++) {
                            bytes[0] = builder.CreateOr(bytes[0], builder.CreateShl(bytes[j], j * 8));
                        }
                        //set the original operand as bytes[0]
                        I.setOperand(i, bytes[0]);
#ifdef EACH_BLOCK_ONLY_ONE_OBFS
                        goto next_bb;
#endif
                        break;
                    }
                    iter = I.getIterator();
                    iter++;
                }
                next_bb:
                ;
            }
        }

        bool runOnFunction(Function &F) override {
            srandom(time(NULL));

            //demote SSA ir to NON-SSA ir, so that the phi-node can't fuck us
            FunctionPass *demote_reg_to_memory = createDemoteRegisterToMemoryPass();
            demote_reg_to_memory->runOnFunction(F);

            if (OPEN_CRYPTO_OPAQUE_PREDICATE) {
                insertCryptoOP(F);
            }

            if (OPEN_FACTOR_OPAQUE_PREDICATE) {
                insertFactorOP(F);
            }

            if (OPEN_LOOP_OPAQUE_PREDICATE) {
                insertLoopOP(F);
            }

            if (OPEN_SYMBOLIC_MEMORY_SNIPPET) {
                insertSymbolicMemorySnippet(F);
            }

            if (OPEN_MEMORY_DETAINT) {
                insertMemoryAttackTaint(F);
            }

            if (OPEN_OPAQUE_CONST_DETAINT) {
                insertOPConstAttackTaint(F);
            }


            return false;
        }
    };

    char Obfuscation::ID = 0;
    static RegisterPass<Obfuscation> X("obfs", "Code Obfuscation Pass", false, false);
}
