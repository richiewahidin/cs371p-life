#!/usr/bin/env python3
import sys

def main(celltype: str):
    # place files in order that their contents
    # should be brought into the output file
    input_files = [
        "AbstractCell.hpp",
        "AbstractCell.cpp",
        "ConwayCell.hpp",
        "ConwayCell.cpp",
        "FredkinCell.hpp",
        "FredkinCell.cpp",
        "Cell.hpp",
        "Cell.cpp",
        "Life.hpp",
    ]
    if celltype == "ConwayCell":
        input_files.append("RunLifeConway.cpp")
    elif celltype == "FredkinCell":
        input_files.append("RunLifeFredkin.cpp")
    else:
        input_files.append("RunLifeCell.cpp")

    # name of the created file
    output_file = "HackerRank" + celltype + ".cpp"

    # list that will contain lines from all the input files
    contents = []

    # read the files
    for file in input_files:
        with open(file, "r") as f:
            contents.extend(f.read().split("\n"))

    # write to the output file
    with open(output_file, "w") as f:
        for line in contents:
            # skip lines that include header files
            if not ("include" in line and ".hpp" in line):
                f.write(line + "\n")
			
if __name__ == "__main__":
	cell_type = sys.argv[1]
	main(cell_type)