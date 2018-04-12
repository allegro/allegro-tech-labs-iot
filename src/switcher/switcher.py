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
        git = repo.git
        git.reset('HEAD~3')
        git.pull()
        git.checkout('{}'.format(args['<stage_id>']))
        repo.active_branch


if __name__ == "__main__":
    main()
