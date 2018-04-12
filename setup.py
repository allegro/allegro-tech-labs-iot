# -*- encoding: utf-8 -*-
import os
import sys
import uuid
from distutils.core import setup

from setuptools import find_packages
from pip.req import parse_requirements


assert sys.version_info >= (2, 7), "Python 2.7+ required."

current_dir = os.path.abspath(os.path.dirname(__file__))
with open(os.path.join(current_dir, 'README.md')) as readme_file:
    long_description = readme_file.read()

sys.path.insert(0, current_dir + os.sep + 'src')
from switcher import VERSION
release = ".".join(str(num) for num in VERSION)

requirements = [str(ir.req) for ir in parse_requirements('{}/requirements/base.txt'.format(current_dir),
                                                         session=uuid.uuid1())]

setup(
    name='switch-level',
    version=release,
    author='Artur Maćkowiak',
    author_email='artur.mackowiak@allegro.pl',
    description="Switcher for stages",
    long_description=long_description,
    install_requires=requirements,
    keywords='',
    platforms=['any'],
    license='Apache Software License v2.0',
    packages=find_packages('src'),
    include_package_data=True,
    package_dir={'': 'src'},
    zip_safe=False,
    console=['src/switcher/switcher.py'],
    entry_points={
        'console_scripts': [
            'switch-level=switcher.switcher:main',
        ],
    },
    zipfile=None,
    classifiers=[
        'Development Status :: 4 - Beta',
        'Intended Audience :: System Administrators',
        'License :: OSI Approved :: Apache Software License',
        'Natural Language :: English',
        'Operating System :: POSIX',
        'Operating System :: MacOS :: MacOS X',
        'Operating System :: Microsoft :: Windows :: Windows NT/2000',
        'Programming Language :: Python',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 2 :: Only',
        'Topic :: Internet :: WWW/HTTP',
    ]
)
