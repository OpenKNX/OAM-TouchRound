// OFM-FunctionBlocks --
// SPDX-License-Identifier: AGPL-3.0-only

function tchAddChannel(device, online, progress, context) {
    var numberOfChannelds = device.getParameterByName('TCH_VisibleChannels');
    var newNumberOfChannels = numberOfChannelds.value + 1;
    // var channelType = device.getParameterByName('TCH_CH' + newNumberOfChannels + 'DeviceType');
    // var notAllowed = device.getParameterByName('TCH_AddNotAllowed');
    // if (channelType == 0)
    // {
    //     notAllowed.value = 1;
    // }
    // else
    // {
    //     notAllowed.value = 0;
         numberOfChannelds.value = newNumberOfChannels;
    // }
}

// -- OFM-FunctionBlocks //
