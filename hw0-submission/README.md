# Homework 0

> Due: 01-15-2021 11:59:59 PM

The goal of this homework is to familiarze the homework submission process.
And implement `insertion_sort`.

**Corresponding Topic**: Design and Analysis of Algorithms, _Running CPP, CMake Files_

## Table of Contents

1. Homework Content
2. CMakeFiles
3. Building Your Homework

## Homework Content

IMPORTANT: **DO NOT CHANGE THE SECTION MARKED WITH**

```cpp
/** DO NOT CHANGE **/
...
/** DO NOT CHANGE **/
```

0. Build the homework with one of the three options in section Building your Homework..

1. Edit `main.cpp` to implement the I/O Interface.

   - We will only check for `./main [INPUT_FILE] [OUTPUT_FILE]`
     and compare the output files with expected for final grading

2. Implement the necessary functions to store the input file
   into IntSequence.

3. Edit `insertion_sort.cpp` to implement Insertion Sort

### Input Format

We will provide some sample test in `input/` folder. The input file format
is the following:

- Line 1 is a single integer $n$
- Line 2 is a series of $n$ integer separated by a space.

You can assume the input format is consistent for all test cases.

### Output Format

The expected output, provided in `expected/` is a single line with sorted list of integers.

### Submitting your Homework

run

```bash
chmod +x generate_submission

./generate_submission
```

The script `generate_submission` will create a zip file `hw0-submission.zip`.
Please submit `hw0-submission.zip`

## CMakeFiles

The official description:

> CMake is an open-source, cross-platform family of tools designed to build, test and package software. CMake is used to control the software compilation process using simple platform and compiler independent configuration files, and generate native makefiles and workspaces that can be used in the compiler environment of your choice

In short: **CMake** is a very sophisticated tool for you to build/run/test/deploy CPP programs.

CMake is:

1. Open-source - Meaning we don't have to pay to use it

2. Cross-Platform - You can run this tool on any\* operating system.

3. used to Build + Test + Package Software

Like all tools, the meaning of its existence is to allow people to use itself. Since this course is based off of CPP, taking this opportunity to learn how to build with CMake will be great benefit to your future as a software engineer.

### CMakeLists File

For line-by-line description, refer to [CMakeLists File](./CMakeLists.txt) in homework 0.

`CMakeLists.txt` file defines the configuration for cmake.

## Building Your Homework

Run the following commands in your homework root directory.

### Running Locally

```bash
mkdir build
cd build
cmake ..
make
./main [INPUT_FILE] [OUTPUT_FILE]
```

### Docker [Optional]

Due to the pandemic, some students may not be able to access the internet
or CSIF. We will provide a docker image for you to run the code locally.

Commercially, Docker is used to streamline deployment of an application. It achieves such goal by bundling your application and its required dependencies into an OS-independent container. Think of a more beefed virtual environment.

You can read more about how docker works [here](<https://en.wikipedia.org/wiki/Docker_(software)>).

For homework, you only need to install docker [here](https://docs.docker.com/engine/install/). (**Warning**: You will need internet when you first download docker. Please do not start the homework at the last minute.)

In order to run the homework,

```bash
docker build .
```

You should see:

```bash
...
Successfully built IMAGE_ID
```

You can get your container name with

```bash
docker run -it IMAGE_ID /bin/bash
```

This command will allows you to run docker container interactively. 

You should see a new prompt with.

```bash
bash-5.0#
```

Continue run the building process described in section [Running Locally](<Running\ Locally>)

*Note*: This workflow is not requird.  Feel free to change Dockerfile to make your debugging more convenient.

### CSIF

Information about using CSIF computers, such as how to remotely login to CSIF
computers from home and how to copy files to/from the CSIF computers using your
personal computer, can be found at [http://csifdocs.cs.ucdavis.edu/about-us]([http://csifdocs.cs.ucdavis.edu/about-us)
csif-general-faq.
