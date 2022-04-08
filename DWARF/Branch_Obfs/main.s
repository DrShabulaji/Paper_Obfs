	.text
	.file	"library.cpp"
	.section	.text.startup,"ax",@progbits
	.p2align	4, 0x90                         # -- Begin function __cxx_global_var_init
	.type	__cxx_global_var_init,@function
__cxx_global_var_init:                  # @__cxx_global_var_init
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movabsq	$_ZStL8__ioinit, %rdi
	callq	_ZNSt8ios_base4InitC1Ev
	movabsq	$_ZNSt8ios_base4InitD1Ev, %rdi
	movabsq	$_ZStL8__ioinit, %rsi
	movabsq	$__dso_handle, %rdx
	callq	__cxa_atexit
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	__cxx_global_var_init, .Lfunc_end0-__cxx_global_var_init
	.cfi_endproc
                                        # -- End function
	.text
	.globl	_Z15throw_exceptionv            # -- Begin function _Z15throw_exceptionv
	.p2align	4, 0x90
	.type	_Z15throw_exceptionv,@function
_Z15throw_exceptionv:                   # @_Z15throw_exceptionv
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	$4, %edi
	callq	__cxa_allocate_exception
	movq	%rax, %rdi
	movl	$1, (%rdi)
	movabsq	$_ZTIi, %rsi
	xorl	%eax, %eax
	movl	%eax, %edx
	callq	__cxa_throw
.Lfunc_end1:
	.size	_Z15throw_exceptionv, .Lfunc_end1-_Z15throw_exceptionv
	.cfi_endproc
                                        # -- End function
	.globl	_Z21wrapper_show_obfs_bb2Pl     # -- Begin function _Z21wrapper_show_obfs_bb2Pl
	.p2align	4, 0x90
	.type	_Z21wrapper_show_obfs_bb2Pl,@function
_Z21wrapper_show_obfs_bb2Pl:            # @_Z21wrapper_show_obfs_bb2Pl
.Lfunc_begin0:
	.cfi_startproc
	.cfi_personality 3, __gxx_personality_v0
	.cfi_lsda 3, .Lexception0
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
.Ltmp0:
	callq	_Z15throw_exceptionv
.Ltmp1:
	jmp	.LBB2_1
.LBB2_1:
	jmp	.LBB2_5
.LBB2_2:
.Ltmp2:
	movq	%rax, %rcx
	movl	%edx, %eax
	movq	%rcx, -16(%rbp)
	movl	%eax, -20(%rbp)
# %bb.3:
	movl	-20(%rbp), %eax
	movl	$1, %ecx
	cmpl	%ecx, %eax
	jne	.LBB2_6
# %bb.4:
	movq	-16(%rbp), %rdi
	callq	__cxa_begin_catch
	movsd	(%rax), %xmm0                   # xmm0 = mem[0],zero
	movsd	%xmm0, -32(%rbp)
	movq	show_obfs_bb2, %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, (%rax)
	callq	__cxa_end_catch
.LBB2_5:
	addq	$32, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.LBB2_6:
	.cfi_def_cfa %rbp, 16
	movq	-16(%rbp), %rdi
	callq	_Unwind_Resume@PLT
.Lfunc_end2:
	.size	_Z21wrapper_show_obfs_bb2Pl, .Lfunc_end2-_Z21wrapper_show_obfs_bb2Pl
	.cfi_endproc
	.section	.gcc_except_table,"a",@progbits
	.p2align	2
GCC_except_table2:
.Lexception0:
	.byte	255                             # @LPStart Encoding = omit
	.byte	3                               # @TType Encoding = udata4
	.uleb128 .Lttbase0-.Lttbaseref0
.Lttbaseref0:
	.byte	1                               # Call site Encoding = uleb128
	.uleb128 .Lcst_end0-.Lcst_begin0
.Lcst_begin0:
	.uleb128 .Ltmp0-.Lfunc_begin0           # >> Call Site 1 <<
	.uleb128 .Ltmp1-.Ltmp0                  #   Call between .Ltmp0 and .Ltmp1
	.uleb128 .Ltmp2-.Lfunc_begin0           #     jumps to .Ltmp2
	.byte	1                               #   On action: 1
	.uleb128 .Ltmp1-.Lfunc_begin0           # >> Call Site 2 <<
	.uleb128 .Lfunc_end2-.Ltmp1             #   Call between .Ltmp1 and .Lfunc_end2
	.byte	0                               #     has no landing pad
	.byte	0                               #   On action: cleanup
.Lcst_end0:
	.byte	1                               # >> Action Record 1 <<
                                        #   Catch TypeInfo 1
	.byte	0                               #   No further actions
	.p2align	2
                                        # >> Catch TypeInfos <<
	.long	_ZTId                           # TypeInfo 1
.Lttbase0:
	.p2align	2
                                        # -- End function
	.text
	.globl	_Z21wrapper_show_obfs_bb1Pl     # -- Begin function _Z21wrapper_show_obfs_bb1Pl
	.p2align	4, 0x90
	.type	_Z21wrapper_show_obfs_bb1Pl,@function
_Z21wrapper_show_obfs_bb1Pl:            # @_Z21wrapper_show_obfs_bb1Pl
.Lfunc_begin1:
	.cfi_startproc
	.cfi_personality 3, __gxx_personality_v0
	.cfi_lsda 3, .Lexception1
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
.Ltmp3:
	callq	_Z21wrapper_show_obfs_bb2Pl
.Ltmp4:
	jmp	.LBB3_1
.LBB3_1:
	jmp	.LBB3_5
.LBB3_2:
.Ltmp5:
	movq	%rax, %rcx
	movl	%edx, %eax
	movq	%rcx, -16(%rbp)
	movl	%eax, -20(%rbp)
# %bb.3:
	movl	-20(%rbp), %eax
	movl	$1, %ecx
	cmpl	%ecx, %eax
	jne	.LBB3_6
# %bb.4:
	movq	-16(%rbp), %rdi
	callq	__cxa_begin_catch
	movl	(%rax), %eax
	movl	%eax, -24(%rbp)
	movq	show_obfs_bb1, %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, (%rax)
	callq	__cxa_end_catch
.LBB3_5:
	addq	$32, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.LBB3_6:
	.cfi_def_cfa %rbp, 16
	movq	-16(%rbp), %rdi
	callq	_Unwind_Resume@PLT
.Lfunc_end3:
	.size	_Z21wrapper_show_obfs_bb1Pl, .Lfunc_end3-_Z21wrapper_show_obfs_bb1Pl
	.cfi_endproc
	.section	.gcc_except_table,"a",@progbits
	.p2align	2
GCC_except_table3:
.Lexception1:
	.byte	255                             # @LPStart Encoding = omit
	.byte	3                               # @TType Encoding = udata4
	.uleb128 .Lttbase1-.Lttbaseref1
.Lttbaseref1:
	.byte	1                               # Call site Encoding = uleb128
	.uleb128 .Lcst_end1-.Lcst_begin1
.Lcst_begin1:
	.uleb128 .Ltmp3-.Lfunc_begin1           # >> Call Site 1 <<
	.uleb128 .Ltmp4-.Ltmp3                  #   Call between .Ltmp3 and .Ltmp4
	.uleb128 .Ltmp5-.Lfunc_begin1           #     jumps to .Ltmp5
	.byte	1                               #   On action: 1
	.uleb128 .Ltmp4-.Lfunc_begin1           # >> Call Site 2 <<
	.uleb128 .Lfunc_end3-.Ltmp4             #   Call between .Ltmp4 and .Lfunc_end3
	.byte	0                               #     has no landing pad
	.byte	0                               #   On action: cleanup
.Lcst_end1:
	.byte	1                               # >> Action Record 1 <<
                                        #   Catch TypeInfo 1
	.byte	0                               #   No further actions
	.p2align	2
                                        # >> Catch TypeInfos <<
	.long	_ZTIi                           # TypeInfo 1
.Lttbase1:
	.p2align	2
                                        # -- End function
	.text
	.globl	_Z4jumpv                        # -- Begin function _Z4jumpv
	.p2align	4, 0x90
	.type	_Z4jumpv,@function
_Z4jumpv:                               # @_Z4jumpv
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	leaq	-8(%rbp), %rdi
	callq	_Z21wrapper_show_obfs_bb1Pl
	movq	-8(%rbp), %rax
	#APP
	movq	%rax, 8(%rbp)
	#NO_APP
	addq	$16, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end4:
	.size	_Z4jumpv, .Lfunc_end4-_Z4jumpv
	.cfi_endproc
                                        # -- End function
	.globl	_Z4showi                        # -- Begin function _Z4showi
	.p2align	4, 0x90
	.type	_Z4showi,@function
_Z4showi:                               # @_Z4showi
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.LBB5_2
# %bb.1:
	movabsq	$.L.str, %rdi
	movb	$0, %al
	callq	printf
	jmp	.LBB5_3
.LBB5_2:
	movabsq	$.L.str.1, %rdi
	movb	$0, %al
	callq	printf
.LBB5_3:
	movabsq	$.L.str.2, %rdi
	movb	$0, %al
	callq	printf
	addq	$16, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end5:
	.size	_Z4showi, .Lfunc_end5-_Z4showi
	.cfi_endproc
                                        # -- End function
	.globl	_Z9show_obfsi                   # -- Begin function _Z9show_obfsi
	.p2align	4, 0x90
	.type	_Z9show_obfsi,@function
_Z9show_obfsi:                          # @_Z9show_obfsi
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	$.Ltmp6, show_obfs_bb1(%rip)
	movq	$.Ltmp7, show_obfs_bb2(%rip)
	cmpl	$1, -4(%rbp)
	je	.LBB6_2
# %bb.1:
	movl	type_of_int, %ecx
	movq	show_obfs_bb2_type, %rax
	movl	%ecx, (%rax)
.LBB6_2:
	callq	_Z4jumpv
	cmpl	$114514, -4(%rbp)               # imm = 0x1BF52
	jne	.LBB6_5
# %bb.3:
	jmp	.LBB6_4
.Ltmp6:                                 # Block address taken
.LBB6_4:
	movabsq	$.L.str, %rdi
	movb	$0, %al
	callq	printf
	jmp	.LBB6_7
.LBB6_5:
	jmp	.LBB6_6
.Ltmp7:                                 # Block address taken
.LBB6_6:
	movabsq	$.L.str.1, %rdi
	movb	$0, %al
	callq	printf
	movl	type_of_double, %ecx
	movq	show_obfs_bb2_type, %rax
	movl	%ecx, (%rax)
.LBB6_7:
	movabsq	$.L.str.2, %rdi
	movb	$0, %al
	callq	printf
	addq	$16, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end6:
	.size	_Z9show_obfsi, .Lfunc_end6-_Z9show_obfsi
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	show_obfs_bb2_type, %rax
	movl	$4096, %ecx                     # imm = 0x1000
	cqto
	idivq	%rcx
	cmpq	$0, %rdx
	je	.LBB7_2
# %bb.1:
	movq	show_obfs_bb2_type, %rax
	movl	$4096, %ecx                     # imm = 0x1000
	cqto
	idivq	%rcx
	movq	%rax, %rdi
	shlq	$12, %rdi
	movl	$8, %esi
	movl	$3, %edx
	callq	mprotect
	jmp	.LBB7_3
.LBB7_2:
	movq	show_obfs_bb2_type, %rdi
	movl	$8, %esi
	movl	$3, %edx
	callq	mprotect
.LBB7_3:
	movl	-8(%rbp), %edi
	callq	_Z9show_obfsi
	xorl	%eax, %eax
	addq	$16, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end7:
	.size	main, .Lfunc_end7-main
	.cfi_endproc
                                        # -- End function
	.section	.text.startup,"ax",@progbits
	.p2align	4, 0x90                         # -- Begin function _GLOBAL__sub_I_library.cpp
	.type	_GLOBAL__sub_I_library.cpp,@function
_GLOBAL__sub_I_library.cpp:             # @_GLOBAL__sub_I_library.cpp
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	callq	__cxx_global_var_init
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end8:
	.size	_GLOBAL__sub_I_library.cpp, .Lfunc_end8-_GLOBAL__sub_I_library.cpp
	.cfi_endproc
                                        # -- End function
	.type	_ZStL8__ioinit,@object          # @_ZStL8__ioinit
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	__dso_handle
	.type	show_obfs_bb1,@object           # @show_obfs_bb1
	.bss
	.globl	show_obfs_bb1
	.p2align	3
show_obfs_bb1:
	.quad	0
	.size	show_obfs_bb1, 8

	.type	show_obfs_bb2,@object           # @show_obfs_bb2
	.globl	show_obfs_bb2
	.p2align	3
show_obfs_bb2:
	.quad	0
	.size	show_obfs_bb2, 8

	.type	show_obfs_bb2_type,@object      # @show_obfs_bb2_type
	.globl	show_obfs_bb2_type
	.p2align	3
show_obfs_bb2_type:
	.quad	0
	.size	show_obfs_bb2_type, 8

	.type	type_of_int,@object             # @type_of_int
	.globl	type_of_int
	.p2align	2
type_of_int:
	.long	0                               # 0x0
	.size	type_of_int, 4

	.type	type_of_double,@object          # @type_of_double
	.globl	type_of_double
	.p2align	2
type_of_double:
	.long	0                               # 0x0
	.size	type_of_double, 4

	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"1\n"
	.size	.L.str, 3

	.type	.L.str.1,@object                # @.str.1
.L.str.1:
	.asciz	"Not 1\n"
	.size	.L.str.1, 7

	.type	.L.str.2,@object                # @.str.2
.L.str.2:
	.asciz	"END\n"
	.size	.L.str.2, 5

	.section	.init_array,"aw",@init_array
	.p2align	3
	.quad	_GLOBAL__sub_I_library.cpp
	.ident	"Debian clang version 13.0.1-3+b1"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __cxx_global_var_init
	.addrsig_sym __cxa_atexit
	.addrsig_sym _Z15throw_exceptionv
	.addrsig_sym __cxa_allocate_exception
	.addrsig_sym __cxa_throw
	.addrsig_sym _Z21wrapper_show_obfs_bb2Pl
	.addrsig_sym __gxx_personality_v0
	.addrsig_sym __cxa_begin_catch
	.addrsig_sym __cxa_end_catch
	.addrsig_sym _Z21wrapper_show_obfs_bb1Pl
	.addrsig_sym _Z4jumpv
	.addrsig_sym printf
	.addrsig_sym _Z9show_obfsi
	.addrsig_sym mprotect
	.addrsig_sym _GLOBAL__sub_I_library.cpp
	.addrsig_sym _Unwind_Resume
	.addrsig_sym _ZStL8__ioinit
	.addrsig_sym __dso_handle
	.addrsig_sym show_obfs_bb1
	.addrsig_sym show_obfs_bb2
	.addrsig_sym show_obfs_bb2_type
	.addrsig_sym type_of_int
	.addrsig_sym type_of_double
	.addrsig_sym _ZTIi
	.addrsig_sym _ZTId
