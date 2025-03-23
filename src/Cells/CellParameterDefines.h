#undef TCH_ParamCalcIndex
#define TCH_ParamCellBlockSize (TCH_CHJumpToLong2 - TCH_CHJumpToLong1)
#define TCH_ParamCalcIndex(index) (index + TCH_ParamBlockOffset + _channelIndex * TCH_ParamBlockSize + _cellIndex * TCH_ParamCellBlockSize)
