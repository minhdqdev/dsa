import os
import sys
from pathlib import Path
from shutil import copy

if __name__ == '__main__':
    problem_name = input('Problem name: ')

    if not problem_name:
        print('Problem name can\'t be empty. Program exited with code 1.')
        sys.exit(1)
    elif len(problem_name) > 128:
        print("Problem name is too long (>128). Program exited with code 1.")
        sys.exit(1)
    
    base_dir = os.path.dirname(os.path.abspath(__file__))

    Path(os.path.join(base_dir, problem_name)).mkdir(parents=True, exist_ok=True)

    language = ''
    while not language:
        ans = input("Choose language:\n  1. Python\n  2. C++\n\n Your choice: ")

        if ans == '1':
            language = 'python'
        elif ans == '2':
            language = 'c++'
        else:
            print('Invalid choice. Please try again.')

    if language == 'c++':
        code_path = Path(os.path.join(base_dir, problem_name, 'main.cpp'))
        snippet_path = Path(os.path.join(base_dir, 'snippet.cpp'))

    elif language == 'python':
        code_path = Path(os.path.join(base_dir, problem_name, 'main.py'))
        snippet_path = Path(os.path.join(base_dir, 'snippet.py'))


    if code_path.exists():
        ans = input('Folder is not empty. Do you want to overwrite it <y/N>? ')

        if ans.lower() in ('y', 'yes'):
            copy(snippet_path, code_path)
        else:
            pass
    else:
        copy(snippet_path, code_path)

    print('Done !')
    sys.exit(0)
    
