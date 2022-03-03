import os
import angr
import claripy
import time
import sys

def compile():
    elf_file = []
    source_path = "./ObfsPaper/for/for/"
    for source in os.listdir(source_path):
        if not (source.endswith(".elf")):
            continue

        elf_file.append(source_path + source)
    return elf_file

def killForWithSecret(program, secret):
        name = program[program.rfind("/") + 1:]

        proj = angr.Project(program, auto_load_libs=True)
        input = claripy.BVS("x", 8 * 4)
        #state = proj.factory.entry_state()
        state = proj.factory.entry_state(argc=2, args=[program, input])
        #proj.factory.call_state()
        #open veritesting feature
        simgr = proj.factory.simgr(state)
        main_func = proj.loader.find_symbol("main").rebased_addr

        while simgr.active[0].solver.eval(simgr.active[0].ip) != main_func:
            simgr.step()

        state = simgr.active[0]
        simgr = proj.factory.simgr(state)
        simgr.use_technique(angr.exploration_techniques.Veritesting(loop_unrolling_limit=256))
        t1 = time.time()
        print("SECRET: " + hex(secret))
        simgr.explore(find=secret)
        t2 = time.time()
        if len(simgr.found) > 0:
            #take[name] = 
            print(name, [t2 - t1, hex(simgr.found[0].solver.eval(input))])

def killFor(program):
        name = program[program.rfind("/") + 1:]
        proj = angr.Project(program, auto_load_libs=False)
        puts_func = proj.loader.find_symbol("puts").rebased_addr

        cfg = proj.analyses.CFGFast()
        for node in cfg.graph.nodes:
            for succ in node.successors:
                if succ.addr == puts_func:
                    secret = node.predecessors[0].addr
                    break
        proj = angr.Project(program, auto_load_libs=True)
        input = claripy.BVS("x", 8 * 4)
        #state = proj.factory.entry_state()
        state = proj.factory.entry_state(argc=2, args=[program, input])
        #proj.factory.call_state()
        #open veritesting feature
        simgr = proj.factory.simgr(state)
        main_func = proj.loader.find_symbol("main").rebased_addr

        while simgr.active[0].solver.eval(simgr.active[0].ip) != main_func:
            simgr.step()

        state = simgr.active[0]
        simgr = proj.factory.simgr(state)
        simgr.use_technique(angr.exploration_techniques.Veritesting(loop_unrolling_limit=256))
        t1 = time.time()
        print("SECRET: " + hex(secret))
        simgr.explore(find=secret)
        t2 = time.time()
        if len(simgr.found) > 0:
            #take[name] = 
            print(name, [t2 - t1, hex(simgr.found[0].solver.eval(input))])

def killCommon():
    elf = compile()
    take = {}
    for program in elf:
        name = program[program.rfind("/") + 1:]
        if not name.startswith("4_"):
            continue
        proj = angr.Project(program, auto_load_libs=False)
        puts_func = proj.loader.find_symbol("puts").rebased_addr

        cfg = proj.analyses.CFGFast()
        for node in cfg.graph.nodes:
            for succ in node.successors:
                if succ.addr == puts_func:
                    secret = node.predecessors[0].addr
                    break
        proj = angr.Project(program, auto_load_libs=True)
        input = claripy.BVS("x", 8 * 4)
        #state = proj.factory.entry_state()
        state = proj.factory.entry_state(argc=2, args=[program, input])
        #proj.factory.call_state()
        #open veritesting feature
        simgr = proj.factory.simgr(state)
        main_func = proj.loader.find_symbol("main").rebased_addr

        while simgr.active[0].solver.eval(simgr.active[0].ip) != main_func:
            simgr.step()

        state = simgr.active[0]
        simgr = proj.factory.simgr(state)
        simgr.use_technique(angr.exploration_techniques.Veritesting(loop_unrolling_limit=256))
        t1 = time.time()
        print("SECRET: " + hex(secret))
        simgr.explore(find=secret)
        t2 = time.time()
        if len(simgr.found) > 0:
            take[name] = [t2 - t1, hex(simgr.found[0].solver.eval(input))]
            print(name, take[name])
    
    print(take)
    f = open("D:\\output_3.txt", "w")
    f.write(str(take))
    f.close()
    
    
    for program in elf:
        name = program[program.rfind("/") + 1:]
        if not name.startswith("4_"):
            continue
        proj = angr.Project(program, auto_load_libs=False)
        puts_func = proj.loader.find_symbol("puts").rebased_addr

        cfg = proj.analyses.CFGFast()
        for node in cfg.graph.nodes:
            for succ in node.successors:
                if succ.addr == puts_func:
                    secret = node.predecessors[0].addr
                    break
        proj = angr.Project(program, auto_load_libs=True)
        input = claripy.BVS("x", 8 * 4)
        #state = proj.factory.entry_state()
        state = proj.factory.entry_state(argc=2, args=[program, input])
        #proj.factory.call_state()
        #open veritesting feature
        simgr = proj.factory.simgr(state)
        main_func = proj.loader.find_symbol("main").rebased_addr

        while simgr.active[0].solver.eval(simgr.active[0].ip) != main_func:
            simgr.step()

        state = simgr.active[0]
        simgr = proj.factory.simgr(state)
        simgr.use_technique(angr.exploration_techniques.Veritesting(loop_unrolling_limit=256))
        t1 = time.time()
        print("SECRET: " + hex(secret))
        simgr.explore(find=secret)
        t2 = time.time()
        if len(simgr.found) > 0:
            take[name] = [t2 - t1, hex(simgr.found[0].solver.eval(input))]
    
    print(take)
    f = open("D:\\output_4.txt", "w")
    f.write(str(take))
    f.close()
def killHardened():
    #source_path = "../hade-master/experimental_data/src/secretFinding/for/"
    source_path = "../hade-master/hardened/secret_finding/for5/"
    #elf = compile()
    #elf = {"file_5.elf" : 0x4012ba}
    elf = {"file_3.elf" : 0x401302, "file_0.elf" : 0x4012d0, "file_1.elf" : 0x4012e9, "file_4.elf" : 0x4012ba, "file_5.elf" : 0x4012ba, "file_8.elf" : 0x4012ba}
    #for program in elf:
    for (program, secret) in elf.items():
        if program.find("1_") == -1:
            continue
        proj = angr.Project(source_path + program, auto_load_libs=True)

        input = claripy.BVS("x", 8 * 20)
        #state = proj.factory.entry_state()
        state = proj.factory.entry_state(argc=2, args=[source_path + program, input])
        #proj.factory.call_state()
        #open veritesting feature
        simgr = proj.factory.simgr(state)
        main_func = proj.loader.find_symbol("main").rebased_addr

        while simgr.active[0].solver.eval(simgr.active[0].ip) != main_func:
            simgr.step()

        state = simgr.active[0]
        simgr = proj.factory.simgr(state)
        simgr.use_technique(angr.exploration_techniques.Veritesting(loop_unrolling_limit=256))
        t1 = time.time()
        simgr.explore(find=secret)
        t2 = time.time()
        if len(simgr.found) > 0:
            print("ATTACK " + program + " SUCCESSFULLY!")
            print("TIME: "  + str(t2 - t1))
            print("INPUT: " + hex(simgr.found[0].solver.eval(input)))
        



if __name__ == "__main__":
    print(len(sys.argv))
    if len(sys.argv) == 2:
        killFor(sys.argv[1])
    elif len(sys.argv) == 3:
        killForWithSecret(sys.argv[1], int(sys.argv[2]))
    