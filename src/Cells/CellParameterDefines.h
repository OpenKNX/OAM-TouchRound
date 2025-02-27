#undef TCH_ParamCalcIndex
#define TCH_ParamCellBlockSize (TCH_ChannelJumpToLong2 - TCH_ChannelJumpToLong1)
#define TCH_ParamCalcIndex(index) (index + TCH_ParamBlockOffset + _channelIndex * TCH_ParamBlockSize + _cellIndex * TCH_ParamCellBlockSize)
