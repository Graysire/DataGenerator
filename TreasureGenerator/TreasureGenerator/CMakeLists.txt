# CMakeList.txt : CMake project for TreasureGenerator, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (TreasureGenerator "TreasureGenerator.cpp" "TreasureGenerator.h" "TableEntry.h" "TableEntry.cpp" "Table.h" "Table.cpp" "RandomNumberGenerator.h" "RandomNumberGenerator.cpp"  "EntryData.h" "EntryData.cpp" "Item.h" "Item.cpp" "VariableTableEntry.h" "NumberGenerationStruct.h" "VariableTableEntry.cpp" "ItemConverter.h")

# TODO: Add tests and install targets if needed.
