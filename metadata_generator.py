import os
import shutil

labs = [x for x in os.listdir() if not os.path.isfile(x) and "Lab" in x]

file = open("meta-data.candidate.json", "w")
file.write("[")
id = 0
tests = sorted(os.listdir(os.path.join("base", "test")))
root = os.getcwd()

for lab in labs:
    for problem_id in sorted(os.listdir(lab)):
        if "-" in problem_id:
            continue
        for bug_id in [
            x for x in os.listdir(os.path.join(lab, problem_id)) if "_buggy" in x
        ]:
            
            id = id + 1
            name = bug_id.split("_")[0]

            problem_tests = list(
                filter(lambda x: x.startswith(f'in.{problem_id}'), tests))

            test_input_list = list(f'"test/{x}"'
                             for x in os.listdir(os.path.join("base", "test"))
                             if problem_id in x and "in" in x)

            test_list = list(map(lambda x: f'"{x.split(".")[2]}"', problem_tests))

            dst = os.path.join(lab, "{}-{}".format(problem_id, name))
            os.makedirs(dst, exist_ok=True)
            shutil.copy(os.path.join(lab, problem_id,
                        "{}_buggy.c".format(name)), dst)
            shutil.copy(os.path.join(lab, problem_id,
                        "{}_correct.c".format(name)), dst)
            shutil.copy(os.path.join(lab, problem_id, "Main.c"), dst)
            shutil.copy("config_subject", dst)

            #Setup the local scripts to get test metadata
            shutil.copy("build_subject_local", os.path.join(dst,"build_subject"))
            shutil.copy("run_test_local", os.path.join(dst,"run_test"))
            
            os.chdir(dst)
            os.system("./build_subject") 
            
            passing_tests =[]
            failing_tests =[]
            
            for test in test_list:
                x = os.system("./run_test {}".format(test))
                #print("Response is {}".format(x))
                if x == 0:
                    passing_tests.append(test)
                else:
                    failing_tests.append(test)
            os.system("rm {}".format(name))
                    
            os.chdir(root)

            #Setup the proper scripts
            shutil.copy("build_subject", dst)
            shutil.copy("run_test", dst)

            #print(failing_tests,passing_tests)
            data = """
            {{
                "id":{id},
                "subject":"{lab}",
                "bug_id":"{problem_id}-{name}",
                "source_file": "{bug_id}",
                "reference_file": "Main.c",
                "line_numbers": [],
                "failing_test": [{failing_tests}],
                "passing_test": [{passing_tests}],
                "count_neg": {failing_test_count},
                "count_pos": {passing_test_count},
                "binary_path": "",
                "crash_input": "",
                "exploit_file_list": [{inputs}],
                "test_timeout": 5,
                "bug_type": "Test Failure",
                "language": "c",
                "config_script": "config_subject",
                "build_script": "build_subject",
                "test_script": "run_test"
            }},
            """.format(
                id=id,
                lab=lab,
                name=name,
                problem_id=problem_id,
                bug_id=bug_id,
                correct_file=name+"_correct.c",
                inputs=",".join(test_input_list),
                passing_test_count=len(passing_tests),
                failing_test_count=len(failing_tests),
                failing_tests=','.join(failing_tests),
                passing_tests=','.join(passing_tests),
                tests=','.join(test_list)
            )
            #print(data)
            file.write(data)

file.write("]")
file.close()
