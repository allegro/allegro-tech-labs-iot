# -*- encoding: utf-8 -*-
"""switch-level

Usage:
  switch-level <stage_id>
  switch-level (-h | --help)
  switch-level (-v|--version)

Options:
  -h --help             Show this screen.
  -v --version          Show version.
"""
import git
from docopt import docopt


def main():
    args = docopt(__doc__, version='checker 0.1.0')
    if args['<stage_id>']:
        repo = git.Repo('.')
        cmd = repo.git
        cmd.reset('--hard HEAD')
        cmd.clean('-fd')
        cmd.checkout('{}'.format(args['<stage_id>']))
        cmd.reset('--hard HEAD')
        repo.active_branch


if __name__ == "__main__":
    main()
