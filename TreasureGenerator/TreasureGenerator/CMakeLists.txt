# CMakeList.txt : CMake project for TreasureGenerator, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (DataGenerator "DataGenerator.cpp" "DataGenerator.h" "DataGenerators/TableEntry.h" "DataGenerators/TableEntry.cpp" "DataGenerators/Table.h" "DataGenerators/Table.cpp" "DataGenerators/RNG.h" "DataGenerators/RNG.cpp"  "DataGenerators/EntryData.h" "DataGenerators/EntryData.cpp" "RPGData/Item.h" "RPGData/Item.cpp" "DataGenerators/VariableTableEntry.h" "DataGenerators/NumberGenerationStruct.h" "DataGenerators/VariableTableEntry.cpp" "RPGData/DataConverters/ItemConverter.h" "RPGData/DataConverters/ItemConverter.cpp")

# TODO: Add tests and install targets if needed.
