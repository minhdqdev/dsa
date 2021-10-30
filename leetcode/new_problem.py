import os
import sys
from pathlib import Path
from shutil import copy

if __name__ == '__main__':
    problem_name = input('Problem name: ')

    if not problem_name:
        print('Problem name can\'t be empty. Program exited with code 1.')
        sys.exit(1)
    
    base_dir = os.path.dirname(os.path.abspath(__file__))

    Path(os.path.join(base_dir, problem_name)).mkdir(parents=True, exist_ok=True)

    code_path = Path(os.path.join(base_dir, problem_name, 'main.cpp'))
    snippet_path = Path(os.path.join(base_dir, 'snippet.cpp'))
    snippet_path.touch()

    if code_path.exists():
        ans = input('main.cpp exists. Do you want to overwrite it with snippet.cpp <y/N>? ')

        if ans.lower() in ('y', 'yes'):
            copy(snippet_path, code_path)
        else:
            pass

    print('New problem is created. Program exited with code 0')
    sys.exit(0)
    
