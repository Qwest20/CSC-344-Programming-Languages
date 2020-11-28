import os
import glob
import string
import tarfile
import subprocess
import re


def c_file_handling():

    c_dir = 'csc344/a1'
    # get length and name
    for c_project in glob.glob(os.path.join(c_dir, '*.c')):
        length = len(list(open(c_project)))
        name = os.path.basename(c_project)
        # Open file
        input_file = open(c_project, "r")
        # Read lines
        input_lines = input_file.readlines()
        # If comments, remove them
        new_lines = [x for x in input_lines if "//" not in x]
        newer_lines = [x for x in new_lines if "#" not in x]
        newer_lines = [x for x in new_lines if "printf" not in x]
        identifiers = sorted(set(re.findall('[A-Za-z][0-9A-Za-z_.]*[A-Za-z0-9]|[A-Za-z]',str(newer_lines))),key = str.casefold)

        # HTML File setup
        html_file = open('csc344/a1/c_summary.html', 'w')
        html_msg = """<html>
            <head><p>C Project Summary</p></head>
            <body><a href="main.c">C Project Link</a>
            <p>This is the name of the file: %s</p>
            <p>This is the length of the file: %s</p>
            <p>These are the identifiers: %s</p></body>
            </html>""" % (name, length, identifiers)
        html_file.write(html_msg)
        html_file.close()


def clj_file_handling():

    clj_dir = 'csc344/a2'
    # get length and name
    for clj_project in glob.glob(os.path.join(clj_dir, '*.clj')):
        length = len(list(open(clj_project)))
        name = os.path.basename(clj_project)
        # Open file
        input_file = open(clj_project, "r")
        # Read lines
        input_lines = input_file.readlines()
        # If comments, remove them
        new_lines = [x for x in input_lines if '"' not in x]
        newer_lines = [x for x in new_lines if "(ns mainproject.core)" not in x]
        identifiers = sorted(set(re.findall('[A-Za-z][0-9A-Za-z_.]*[A-Za-z0-9]|[A-Za-z]',str(newer_lines))),key = str.casefold)

        # HTML Stuff
        html_file = open('csc344/a2/clj_summary.html', 'w')
        html_msg = """<html>
            <head><p>Clojure Project Summary</p></head>
            <body><a href="core.clj">Clojure Project Link</a>
            <p>This is the name of the file: %s</p>
            <p>This is the length of the file: %s</p>
            <p>These are the identifiers: %s</p></body>
            </html>""" % (name, length, identifiers)
        html_file.write(html_msg)
        html_file.close()


def scala_file_handling():

    scala_dir = 'csc344/a3'
    # get length and name
    for scala_project in glob.glob(os.path.join(scala_dir, '*.scala')):
        length = len(list(open(scala_project)))
        name = os.path.basename(scala_project)
        # Open file
        input_file = open(scala_project, "r")
        # Read lines
        input_lines = input_file.readlines()
        # If comments, remove them
        new_lines = [x for x in input_lines if '//' not in x]
        newer_lines = [x for x in new_lines if "println" not in x]
        identifiers = sorted(set(re.findall('[A-Za-z][0-9A-Za-z_.]*[A-Za-z0-9]|[A-Za-z]',str(newer_lines))),key = str.casefold)

        # HTML Stuff
        html_file = open('csc344/a3/scala_summary.html', 'w')
        html_msg = """<html>
            <head><p>Scala Project Summary</p></head>
            <body><a href="stringparser.scala">Scala Project Link</a>
            <p>This is the name of the file: %s</p>
            <p>This is the length of the file: %s</p>
            <p>These are the identifiers: %s</p></body>
            </html>""" % (name, length, identifiers)
        html_file.write(html_msg)
        html_file.close()


def pl_file_handling():

    pl_dir = 'csc344/a4'
    # get length and name
    for pl_project in glob.glob(os.path.join(pl_dir, '*.pl')):
        length = len(list(open(pl_project)))
        name = os.path.basename(pl_project)
        # Open file
        input_file = open(pl_project, "r")
        # Read lines
        input_lines = input_file.readlines()
        # If comments, remove them
        new_lines = [x for x in input_lines if '%' not in x]
        identifiers = sorted(set(re.findall('[A-Za-z][0-9A-Za-z_.]*[A-Za-z0-9]|[A-Za-z]',str(new_lines))),key = str.casefold)

        # HTML Stuff
        html_file = open('csc344/a4/pl_summary.html', 'w')
        html_msg = """<html>
            <head><p>Prolog Project Summary</p></head>
            <body><a href="MainProject.pl">Prolog Project Link</a>
            <p>This is the name of the file: %s</p>
            <p>This is the length of the file: %s</p>
            <p>These are the identifiers: %s</p></body>
            </html>""" % (name, length, identifiers)
        html_file.write(html_msg)
        html_file.close()


def py_file_handling():

    py_dir = 'csc344/a5'
    # get length and name
    for py_project in glob.glob(os.path.join(py_dir, '*.py')):
        length = len(list(open(py_project)))
        name = os.path.basename(py_project)
        # Open file
        input_file = open(py_project, "r")
        # Read lines
        input_lines = input_file.readlines()
        # If comments, remove them
        new_lines = [x for x in input_lines if '#' not in x]
        newer_lines = [x for x in new_lines if '<' not in x]
        identifiers = sorted(set(re.findall('[A-Za-z][0-9A-Za-z_.]*[A-Za-z0-9]|[A-Za-z]',str(newer_lines))),key = str.casefold)

        # HTML Stuff
        html_file = open('csc344/a5/py_summary.html', 'w')
        html_msg = """
        <html>
            <head><p>Python Project Summary</p></head>
            <body><a href="main.py">Python Project Link</a>
            <p>This is the name of the file: %s</p>
            <p>This is the length of the file: %s</p>
            <p>These are the identifiers: %s</p></body>
            </html>""" % (name, length, identifiers)
        html_file.write(html_msg)
        html_file.close()


def make_index_file():
    html_file = open('csc344/index.html', 'w')
    html_msg = """<html>
                <head><p>Liam McMahan csc344 Python Project</p></head>
                <body><p><a href="a1/c_summary.html">C Summary</a></p>
                <p><a href="a2/clj_summary.html">Clojure Summary</a></p>
                <p><a href="a3/scala_summary.html">Scala Summary</a></p>
                <p><a href="a4/pl_summary.html">Prolog Summary</a></p>
                <p><a href="a5/py_summary.html">Python Summary</a></p></body>
                </html>"""
    html_file.write(html_msg)
    html_file.close()


def make_tar():
    tar = tarfile.open('qwest.tar', 'w')
    for file in glob.glob('csc344'):
        tar.add(file)
        tar.close()


def send_email(email):
    output = subprocess.run("mutt -s 'Liam McMahan: Python Project' -a qwest.tar -- "+email+ '< /dev/null', shell=True)


def main():
    c_file_handling()
    clj_file_handling()
    scala_file_handling()
    pl_file_handling()
    py_file_handling()
    make_index_file()
    make_tar()
    email = input("Please enter your receiving email: ")
    send_email(email)


main()

