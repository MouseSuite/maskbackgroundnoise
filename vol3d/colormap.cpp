// Copyright (C) 2025 The Regents of the University of California
//
// Created by David W. Shattuck, Ph.D.
//
// This file is part of maskbackgroundnoise.
//
// maskbackgroundnoise is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation, version 2.1.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
//

#include <fstream>
#include <colormap.h>
#include <strutil.h>

ColorMap::ColorMap()
{
  map["grey"] = greyLUT;
  map["hsv"] = hsvLUT;
  map["cool"] = coolLUT;
  map["copper"] = copperLUT;
  map["pink"] = pinkLUT;
  map["prism"] = prismLUT;
  map["bone"] = boneLUT;
  map["jet"] = jetLUT;
  map["hot"] = hotLUT;
  map["red"] = redLUT;
  map["green"] = greenLUT;
  map["blue"] = blueLUT;
  map["inverse"] = greyInverseLUT;
}

void ColorMap::initialize()
{
  for (int i=0;i<256;i++) ColorMap::greyInverseLUT[i] = ColorMap::greyLUT[255-i];
}

class InitializeColorMap {
public:
  InitializeColorMap() { ColorMap::initialize(); }
};

InitializeColorMap initializeColorMap;

bool ColorMap::loadCustomLUT(std::string lutFilename, bool verbose)
{
  std::ifstream ifile(lutFilename);
  if (!ifile) { std::cerr<<"unable to load "<<lutFilename<<std::endl; return false; }
  std::string lutName=StrUtil::getFilename(lutFilename);
  std::vector<uint32> m(256);
  for (auto i=0;i<256;i++)
  {
    float r,g,b;
    ifile>>std::ws>>r>>g>>b;
    uint32 r8=(uint8)(r*255),g8=(uint8)(g*255),b8=(uint8)(b*255);
    m[i]=((r8<<16)&0xFF0000)|((g8<<8)&0xFF00)|(b8&0xFF);
  }
  customMaps.push_back(m);
  if (verbose) std::cout<<"Loaded colormap "<<lutName<<"."<<std::endl;
  map[lutName]=&customMaps.back()[0];
  return true;
}

uint32 ColorMap::hsvLUT[256] = {
  0xff0000,0xff0500,0xff0b00,0xff1100,0xff1700,0xff1d00,0xff2300,0xff2900,0xff2f00,0xff3500,0xff3b00,0xff4100,0xff4700,0xff4d00,0xff5300,0xff5900,
  0xff5f00,0xff6500,0xff6b00,0xff7100,0xff7700,0xff7d00,0xff8300,0xff8900,0xff8f00,0xff9500,0xff9b00,0xffa100,0xffa700,0xffad00,0xffb300,0xffb900,
  0xffbf00,0xffc500,0xffcb00,0xffd100,0xffd700,0xffdd00,0xffe300,0xffe900,0xffef00,0xfff500,0xfffb00,0xfdff00,0xf7ff00,0xf1ff00,0xebff00,0xe5ff00,
  0xdfff00,0xd9ff00,0xd3ff00,0xcdff00,0xc7ff00,0xc1ff00,0xbbff00,0xb5ff00,0xafff00,0xa9ff00,0xa3ff00,0x9dff00,0x97ff00,0x91ff00,0x8bff00,0x85ff00,
  0x7fff00,0x79ff00,0x73ff00,0x6dff00,0x67ff00,0x61ff00,0x5bff00,0x55ff00,0x4fff00,0x49ff00,0x43ff00,0x3dff00,0x37ff00,0x31ff00,0x2bff00,0x25ff00,
  0x1fff00,0x19ff00,0x13ff00,0xdff00,0x7ff00,0x1ff00,0xff03,0xff09,0xff0f,0xff15,0xff1b,0xff21,0xff27,0xff2d,0xff33,0xff39,
  0xff3f,0xff45,0xff4b,0xff51,0xff57,0xff5d,0xff63,0xff69,0xff6f,0xff75,0xff7b,0xff81,0xff87,0xff8d,0xff93,0xff99,
  0xff9f,0xffa5,0xffab,0xffb1,0xffb7,0xffbd,0xffc3,0xffc9,0xffcf,0xffd5,0xffdb,0xffe1,0xffe7,0xffed,0xfff3,0xfff9,
  0xffff,0xf9ff,0xf3ff,0xedff,0xe7ff,0xe1ff,0xdbff,0xd5ff,0xcfff,0xc9ff,0xc3ff,0xbdff,0xb7ff,0xb1ff,0xabff,0xa5ff,
  0x9fff,0x99ff,0x93ff,0x8dff,0x87ff,0x81ff,0x7bff,0x75ff,0x6fff,0x69ff,0x63ff,0x5dff,0x57ff,0x51ff,0x4bff,0x45ff,
  0x3fff,0x39ff,0x33ff,0x2dff,0x27ff,0x21ff,0x1bff,0x15ff,0xfff,0x9ff,0x3ff,0x100ff,0x700ff,0xd00ff,0x1300ff,0x1900ff,
  0x1f00ff,0x2500ff,0x2b00ff,0x3100ff,0x3700ff,0x3d00ff,0x4300ff,0x4900ff,0x4f00ff,0x5500ff,0x5b00ff,0x6100ff,0x6700ff,0x6d00ff,0x7300ff,0x7900ff,
  0x7f00ff,0x8500ff,0x8b00ff,0x9100ff,0x9700ff,0x9d00ff,0xa300ff,0xa900ff,0xaf00ff,0xb500ff,0xbb00ff,0xc100ff,0xc700ff,0xcd00ff,0xd300ff,0xd900ff,
  0xdf00ff,0xe500ff,0xeb00ff,0xf100ff,0xf700ff,0xfd00ff,0xff00fb,0xff00f5,0xff00ef,0xff00e9,0xff00e3,0xff00dd,0xff00d7,0xff00d1,0xff00cb,0xff00c5,
  0xff00bf,0xff00b9,0xff00b3,0xff00ad,0xff00a7,0xff00a1,0xff009b,0xff0095,0xff008f,0xff0089,0xff0083,0xff007d,0xff0077,0xff0071,0xff006b,0xff0065,
  0xff005f,0xff0059,0xff0053,0xff004d,0xff0047,0xff0041,0xff003b,0xff0035,0xff002f,0xff0029,0xff0023,0xff001d,0xff0017,0xff0011,0xff000b,0xff0005,
};

uint32 ColorMap::coolLUT[256] = {
  0xffff,0x1feff,0x2fdff,0x3fcff,0x4fbff,0x5faff,0x6f9ff,0x7f8ff,0x8f7ff,0x9f6ff,0xaf5ff,0xbf4ff,0xcf3ff,0xdf2ff,0xef1ff,0xff0ff,
  0x10efff,0x11eeff,0x12edff,0x13ecff,0x14ebff,0x15eaff,0x16e9ff,0x17e8ff,0x18e7ff,0x19e6ff,0x1ae5ff,0x1be4ff,0x1ce3ff,0x1de2ff,0x1ee1ff,0x1fe0ff,
  0x20dfff,0x21deff,0x22ddff,0x23dcff,0x24dbff,0x25daff,0x26d9ff,0x27d8ff,0x28d7ff,0x29d6ff,0x2ad5ff,0x2bd3ff,0x2cd3ff,0x2dd2ff,0x2ed1ff,0x2fd0ff,
  0x30cfff,0x31ceff,0x32cdff,0x33ccff,0x34cbff,0x35caff,0x36c9ff,0x37c8ff,0x38c7ff,0x39c6ff,0x3ac5ff,0x3bc3ff,0x3cc3ff,0x3dc2ff,0x3ec1ff,0x3fc0ff,
  0x40bfff,0x41beff,0x42bdff,0x43bcff,0x44bbff,0x45baff,0x46b9ff,0x47b8ff,0x48b7ff,0x49b6ff,0x4ab4ff,0x4bb3ff,0x4cb3ff,0x4db2ff,0x4eb1ff,0x4fb0ff,
  0x50afff,0x51aeff,0x52adff,0x53acff,0x54abff,0x55aaff,0x56a9ff,0x57a8ff,0x58a7ff,0x59a6ff,0x5aa4ff,0x5ba3ff,0x5ca3ff,0x5da2ff,0x5ea1ff,0x5fa0ff,
  0x609fff,0x619eff,0x629dff,0x639cff,0x649bff,0x659aff,0x6699ff,0x6798ff,0x6897ff,0x6996ff,0x6a94ff,0x6b93ff,0x6c93ff,0x6d92ff,0x6e91ff,0x6f90ff,
  0x708fff,0x718eff,0x728dff,0x738cff,0x748bff,0x758aff,0x7689ff,0x7788ff,0x7887ff,0x7986ff,0x7a84ff,0x7b83ff,0x7c83ff,0x7d82ff,0x7e81ff,0x7f80ff,
  0x807fff,0x817eff,0x827dff,0x837cff,0x847aff,0x8579ff,0x8679ff,0x8778ff,0x8877ff,0x8976ff,0x8a75ff,0x8b74ff,0x8c72ff,0x8d71ff,0x8e71ff,0x8f70ff,
  0x906fff,0x916eff,0x926dff,0x936cff,0x946aff,0x9569ff,0x9669ff,0x9768ff,0x9867ff,0x9966ff,0x9a65ff,0x9b64ff,0x9c62ff,0x9d61ff,0x9e61ff,0x9f60ff,
  0xa05fff,0xa15eff,0xa25dff,0xa35cff,0xa45aff,0xa559ff,0xa659ff,0xa758ff,0xa857ff,0xa956ff,0xaa55ff,0xab54ff,0xac52ff,0xad51ff,0xae51ff,0xaf50ff,
  0xb04fff,0xb14eff,0xb24dff,0xb34cff,0xb44aff,0xb549ff,0xb649ff,0xb748ff,0xb847ff,0xb946ff,0xba45ff,0xbb44ff,0xbc42ff,0xbd41ff,0xbe41ff,0xbf40ff,
  0xc03fff,0xc13eff,0xc23dff,0xc33cff,0xc43aff,0xc539ff,0xc638ff,0xc738ff,0xc837ff,0xc936ff,0xca35ff,0xcb34ff,0xcc32ff,0xcd31ff,0xce30ff,0xcf30ff,
  0xd02fff,0xd12eff,0xd22dff,0xd32cff,0xd42aff,0xd529ff,0xd628ff,0xd728ff,0xd827ff,0xd926ff,0xda25ff,0xdb24ff,0xdc22ff,0xdd21ff,0xde20ff,0xdf20ff,
  0xe01fff,0xe11eff,0xe21dff,0xe31cff,0xe41aff,0xe519ff,0xe618ff,0xe718ff,0xe817ff,0xe916ff,0xea15ff,0xeb14ff,0xec12ff,0xed11ff,0xee10ff,0xef10ff,
  0xf00fff,0xf10eff,0xf20dff,0xf30cff,0xf40aff,0xf509ff,0xf608ff,0xf708ff,0xf807ff,0xf906ff,0xfa05ff,0xfb04ff,0xfc02ff,0xfd01ff,0xfe00ff,0xff00ff,
};

uint32 ColorMap::copperLUT[256] = {
  0x0,0x10000,0x20100,0x30201,0x50301,0x60302,0x70402,0x80503,0xa0603,0xb0704,0xc0704,0xd0805,0xf0905,0x100a06,0x110a06,0x120b07,
  0x140c07,0x150d08,0x160e08,0x170e09,0x190f09,0x1a100a,0x1b110a,0x1c110b,0x1e120b,0x1f130c,0x20140c,0x21150d,0x23150d,0x24160e,0x25170e,0x26180f,
  0x28180f,0x291910,0x2a1a10,0x2b1b11,0x2c1c11,0x2e1c12,0x2f1d12,0x301e13,0x321f13,0x332014,0x342014,0x352115,0x372215,0x382316,0x392316,0x3a2417,
  0x3c2517,0x3d2618,0x3e2718,0x3f2719,0x412819,0x42291a,0x432a1a,0x442a1b,0x462b1b,0x472c1c,0x482d1c,0x492e1d,0x4b2e1d,0x4c2f1e,0x4d301e,0x4e311f,
  0x50311f,0x513220,0x523320,0x533421,0x553521,0x563522,0x573622,0x583723,0x593823,0x5b3924,0x5c3924,0x5d3a25,0x5f3b25,0x603c26,0x613c26,0x623d27,
  0x643e27,0x653f28,0x664028,0x674029,0x694129,0x6a422a,0x6b432a,0x6c432b,0x6e442b,0x6f452c,0x70462c,0x71472d,0x73472d,0x74482e,0x75492e,0x764a2f,
  0x784a2f,0x794b30,0x7a4c30,0x7b4d31,0x7d4e31,0x7e4e32,0x7f4f32,0x805033,0x825133,0x835234,0x845234,0x855335,0x875435,0x885536,0x895536,0x8a5637,
  0x8c5737,0x8d5838,0x8e5938,0x8f5939,0x915a39,0x925b3a,0x935c3a,0x945c3b,0x965d3b,0x975e3c,0x985f3c,0x99603d,0x9b603d,0x9c613e,0x9d623e,0x9e633f,
  0xa0633f,0xa16440,0xa26540,0xa36641,0xa56741,0xa66742,0xa76842,0xa86943,0xaa6a43,0xab6b44,0xac6b44,0xad6c45,0xaf6d45,0xb06e46,0xb16e46,0xb26f47,
  0xb37047,0xb57148,0xb67248,0xb77249,0xb97349,0xba744a,0xbb754a,0xbc754b,0xbe764b,0xbf774c,0xc0784c,0xc1794d,0xc3794d,0xc47a4e,0xc57b4e,0xc67c4f,
  0xc87c4f,0xc97d50,0xca7e50,0xcb7f51,0xcd8051,0xce8052,0xcf8152,0xd08253,0xd28353,0xd38454,0xd48454,0xd58555,0xd78655,0xd88756,0xd98756,0xda8857,
  0xdc8957,0xdd8a58,0xde8b58,0xdf8b59,0xe18c59,0xe28d5a,0xe38e5a,0xe48e5b,0xe68f5b,0xe7905c,0xe8915c,0xe9925d,0xeb925d,0xec935e,0xed945e,0xee955f,
  0xf0955f,0xf19660,0xf29760,0xf39861,0xf59961,0xf69962,0xf79a62,0xf89b63,0xfa9c63,0xfb9d63,0xfc9d64,0xfd9e64,0xff9f65,0xffa065,0xffa066,0xffa166,
  0xffa267,0xffa367,0xffa468,0xffa468,0xffa569,0xffa669,0xffa76a,0xffa76a,0xffa86b,0xffa96b,0xffaa6c,0xffab6c,0xffab6d,0xffac6d,0xffad6e,0xffae6e,
  0xffae6f,0xffaf6f,0xffb070,0xffb170,0xffb271,0xffb271,0xffb372,0xffb472,0xffb573,0xffb673,0xffb674,0xffb774,0xffb875,0xffb975,0xffb976,0xffba76,
  0xffbb77,0xffbc77,0xffbd78,0xffbd78,0xffbe79,0xffbf79,0xffc07a,0xffc07a,0xffc17b,0xffc27b,0xffc37c,0xffc47c,0xffc47d,0xffc57d,0xffc67e,0xffc77e,
};

uint32 ColorMap::pinkLUT[256] = {
  0xf0000,0x180d0d,0x1f1212,0x251616,0x2a1a1a,0x2e1d1d,0x321f1f,0x362222,0x3a2424,0x3d2727,0x402929,0x432b2b,0x462d2d,0x492f2f,0x4b3030,0x4e3232,
  0x503434,0x533535,0x553737,0x583838,0x5a3a3a,0x5c3b3b,0x5e3d3d,0x603e3e,0x623f3f,0x644141,0x664242,0x684343,0x6a4444,0x6c4646,0x6d4747,0x6f4848,
  0x714949,0x734a4a,0x744c4c,0x764d4d,0x784e4e,0x794f4f,0x7b5050,0x7d5151,0x7e5252,0x805353,0x815454,0x835555,0x845656,0x865757,0x875858,0x895959,
  0x8a5a5a,0x8c5b5b,0x8d5c5c,0x8e5d5d,0x905e5e,0x915e5e,0x925f5f,0x946060,0x956161,0x966262,0x986363,0x996464,0x9a6464,0x9c6565,0x9d6666,0x9e6767,
  0x9f6868,0xa16969,0xa26969,0xa36a6a,0xa46b6b,0xa56c6c,0xa76d6d,0xa86d6d,0xa96e6e,0xaa6f6f,0xab7070,0xac7070,0xae7171,0xaf7272,0xb07373,0xb17373,
  0xb27474,0xb37575,0xb47676,0xb57676,0xb67777,0xb87878,0xb97878,0xba7979,0xbb7a7a,0xbc7b7b,0xbd7b7b,0xbe7c7c,0xbf7d7d,0xc07d7d,0xc17e7e,0xc27f7f,
  0xc2807f,0xc38280,0xc38381,0xc48581,0xc48682,0xc58883,0xc58983,0xc58a84,0xc68c84,0xc68d85,0xc78f86,0xc79086,0xc89187,0xc89388,0xc89488,0xc99589,
  0xc99789,0xca988a,0xca998b,0xcb9b8b,0xcb9c8c,0xcb9d8d,0xcc9e8d,0xcca08e,0xcda18e,0xcda28f,0xcda390,0xcea590,0xcea691,0xcfa791,0xcfa892,0xd0a992,
  0xd0aa93,0xd0ac94,0xd1ad94,0xd1ae95,0xd2af95,0xd2b096,0xd2b196,0xd3b297,0xd3b398,0xd4b598,0xd4b699,0xd4b799,0xd5b89a,0xd5b99a,0xd6ba9b,0xd6bb9b,
  0xd6bc9c,0xd7bd9d,0xd7be9d,0xd8bf9e,0xd8c09e,0xd8c19f,0xd9c29f,0xd9c3a0,0xd9c4a0,0xdac5a1,0xdac6a1,0xdbc7a2,0xdbc8a2,0xdbc9a3,0xdccaa3,0xdccba4,
  0xddcca4,0xddcda5,0xddcea5,0xdecfa6,0xded0a6,0xded1a7,0xdfd2a7,0xdfd3a8,0xe0d4a8,0xe0d5a9,0xe0d6aa,0xe1d7aa,0xe1d7aa,0xe2d8ab,0xe2d9ab,0xe2daac,
  0xe3dbac,0xe3dcad,0xe3ddad,0xe4deae,0xe4dfae,0xe5e0af,0xe5e0af,0xe5e1b0,0xe6e2b0,0xe6e3b1,0xe6e4b1,0xe7e5b2,0xe7e6b2,0xe7e6b3,0xe8e7b3,0xe8e8b4,
  0xe9e9b5,0xe9e9b6,0xe9e9b8,0xeaeab9,0xeaeabb,0xeaeabc,0xebebbd,0xebebbf,0xebebc0,0xececc1,0xececc3,0xededc4,0xededc5,0xededc6,0xeeeec8,0xeeeec9,
  0xeeeeca,0xefefcc,0xefefcd,0xefefce,0xf0f0cf,0xf0f0d0,0xf0f0d2,0xf1f1d3,0xf1f1d4,0xf2f2d5,0xf2f2d6,0xf2f2d8,0xf3f3d9,0xf3f3da,0xf3f3db,0xf4f4dc,
  0xf4f4dd,0xf4f4df,0xf5f5e0,0xf5f5e1,0xf5f5e2,0xf6f6e3,0xf6f6e4,0xf6f6e5,0xf7f7e6,0xf7f7e8,0xf7f7e9,0xf8f8ea,0xf8f8eb,0xf8f8ec,0xf9f9ed,0xf9f9ee,
  0xf9f9ef,0xfafaf0,0xfafaf1,0xfafaf2,0xfbfbf3,0xfbfbf4,0xfbfbf5,0xfcfcf6,0xfcfcf7,0xfcfcf8,0xfdfdf9,0xfdfdfa,0xfdfdfb,0xfefefc,0xfefefe,0xffffff,
};

uint32 ColorMap::greyLUT[256] = {
  0x0,0x10101,0x20202,0x30303,0x40404,0x50505,0x60606,0x70707,0x80808,0x90909,0xa0a0a,0xb0b0b,0xc0c0c,0xd0d0d,0xe0e0e,0xf0f0f,
  0x101010,0x111111,0x121212,0x131313,0x141414,0x151515,0x161616,0x171717,0x181818,0x191919,0x1a1a1a,0x1b1b1b,0x1c1c1c,0x1d1d1d,0x1e1e1e,0x1f1f1f,
  0x202020,0x212121,0x222222,0x232323,0x242424,0x252525,0x262626,0x272727,0x282828,0x292929,0x2a2a2a,0x2b2b2b,0x2c2c2c,0x2d2d2d,0x2e2e2e,0x2f2f2f,
  0x303030,0x313131,0x323232,0x333333,0x343434,0x353535,0x363636,0x373737,0x383838,0x393939,0x3a3a3a,0x3b3b3b,0x3c3c3c,0x3d3d3d,0x3e3e3e,0x3f3f3f,
  0x404040,0x414141,0x424242,0x434343,0x444444,0x454545,0x464646,0x474747,0x484848,0x494949,0x4a4a4a,0x4b4b4b,0x4c4c4c,0x4d4d4d,0x4e4e4e,0x4f4f4f,
  0x505050,0x515151,0x525252,0x535353,0x545454,0x555555,0x565656,0x575757,0x585858,0x595959,0x5a5a5a,0x5b5b5b,0x5c5c5c,0x5d5d5d,0x5e5e5e,0x5f5f5f,
  0x606060,0x616161,0x626262,0x636363,0x646464,0x656565,0x666666,0x676767,0x686868,0x696969,0x6a6a6a,0x6b6b6b,0x6c6c6c,0x6d6d6d,0x6e6e6e,0x6f6f6f,
  0x707070,0x717171,0x727272,0x737373,0x747474,0x757575,0x767676,0x777777,0x787878,0x797979,0x7a7a7a,0x7b7b7b,0x7c7c7c,0x7d7d7d,0x7e7e7e,0x7f7f7f,
  0x808080,0x818181,0x828282,0x838383,0x848484,0x858585,0x868686,0x878787,0x888888,0x898989,0x8a8a8a,0x8b8b8b,0x8c8c8c,0x8d8d8d,0x8e8e8e,0x8f8f8f,
  0x909090,0x919191,0x929292,0x939393,0x949494,0x959595,0x969696,0x979797,0x989898,0x999999,0x9a9a9a,0x9b9b9b,0x9c9c9c,0x9d9d9d,0x9e9e9e,0x9f9f9f,
  0xa0a0a0,0xa1a1a1,0xa2a2a2,0xa3a3a3,0xa4a4a4,0xa5a5a5,0xa6a6a6,0xa7a7a7,0xa8a8a8,0xa9a9a9,0xaaaaaa,0xababab,0xacacac,0xadadad,0xaeaeae,0xafafaf,
  0xb0b0b0,0xb1b1b1,0xb2b2b2,0xb3b3b3,0xb4b4b4,0xb5b5b5,0xb6b6b6,0xb7b7b7,0xb8b8b8,0xb9b9b9,0xbababa,0xbbbbbb,0xbcbcbc,0xbdbdbd,0xbebebe,0xbfbfbf,
  0xc0c0c0,0xc1c1c1,0xc2c2c2,0xc3c3c3,0xc4c4c4,0xc5c5c5,0xc6c6c6,0xc7c7c7,0xc8c8c8,0xc9c9c9,0xcacaca,0xcbcbcb,0xcccccc,0xcdcdcd,0xcecece,0xcfcfcf,
  0xd0d0d0,0xd1d1d1,0xd2d2d2,0xd3d3d3,0xd4d4d4,0xd5d5d5,0xd6d6d6,0xd7d7d7,0xd8d8d8,0xd9d9d9,0xdadada,0xdbdbdb,0xdcdcdc,0xdddddd,0xdedede,0xdfdfdf,
  0xe0e0e0,0xe1e1e1,0xe2e2e2,0xe3e3e3,0xe4e4e4,0xe5e5e5,0xe6e6e6,0xe7e7e7,0xe8e8e8,0xe9e9e9,0xeaeaea,0xebebeb,0xececec,0xededed,0xeeeeee,0xefefef,
  0xf0f0f0,0xf1f1f1,0xf2f2f2,0xf3f3f3,0xf4f4f4,0xf5f5f5,0xf6f6f6,0xf7f7f7,0xf8f8f8,0xf9f9f9,0xfafafa,0xfbfbfb,0xfcfcfc,0xfdfdfd,0xfefefe,0xffffff,
};

uint32 ColorMap::greyInverseLUT[256];

uint32 ColorMap::hotLUT[256] = {
  0x20000,0x50000,0x70000,0xa0000,0xd0000,0xf0000,0x120000,0x150000,0x170000,0x1a0000,0x1d0000,0x1f0000,0x220000,0x250000,0x270000,0x2a0000,
  0x2d0000,0x2f0000,0x320000,0x350000,0x370000,0x3a0000,0x3d0000,0x3f0000,0x420000,0x450000,0x470000,0x4a0000,0x4d0000,0x4f0000,0x520000,0x550000,
  0x570000,0x5a0000,0x5c0000,0x5f0000,0x620000,0x640000,0x670000,0x6a0000,0x6c0000,0x6f0000,0x720000,0x740000,0x770000,0x7a0000,0x7c0000,0x7f0000,
  0x820000,0x840000,0x870000,0x8a0000,0x8c0000,0x8f0000,0x920000,0x940000,0x970000,0x9a0000,0x9c0000,0x9f0000,0xa20000,0xa40000,0xa70000,0xaa0000,
  0xac0000,0xaf0000,0xb10000,0xb40000,0xb70000,0xb90000,0xbc0000,0xbf0000,0xc10000,0xc40000,0xc70000,0xc90000,0xcc0000,0xcf0000,0xd10000,0xd40000,
  0xd70000,0xd90000,0xdc0000,0xdf0000,0xe10000,0xe40000,0xe70000,0xe90000,0xec0000,0xef0000,0xf10000,0xf40000,0xf70000,0xf90000,0xfc0000,0xff0000,
  0xff0200,0xff0500,0xff0700,0xff0a00,0xff0d00,0xff0f00,0xff1200,0xff1500,0xff1700,0xff1a00,0xff1d00,0xff1f00,0xff2200,0xff2500,0xff2700,0xff2a00,
  0xff2d00,0xff2f00,0xff3200,0xff3500,0xff3700,0xff3a00,0xff3d00,0xff3f00,0xff4200,0xff4500,0xff4700,0xff4a00,0xff4d00,0xff4f00,0xff5200,0xff5500,
  0xff5700,0xff5a00,0xff5c00,0xff5f00,0xff6200,0xff6400,0xff6700,0xff6a00,0xff6c00,0xff6f00,0xff7200,0xff7400,0xff7700,0xff7a00,0xff7c00,0xff7f00,
  0xff8200,0xff8400,0xff8700,0xff8a00,0xff8c00,0xff8f00,0xff9200,0xff9400,0xff9700,0xff9a00,0xff9c00,0xff9f00,0xffa200,0xffa400,0xffa700,0xffaa00,
  0xffac00,0xffaf00,0xffb100,0xffb400,0xffb700,0xffb900,0xffbc00,0xffbf00,0xffc100,0xffc400,0xffc700,0xffc900,0xffcc00,0xffcf00,0xffd100,0xffd400,
  0xffd700,0xffd900,0xffdc00,0xffdf00,0xffe100,0xffe400,0xffe700,0xffe900,0xffec00,0xffef00,0xfff100,0xfff400,0xfff700,0xfff900,0xfffc00,0xffff00,
  0xffff03,0xffff07,0xffff0b,0xffff0f,0xffff13,0xffff17,0xffff1b,0xffff1f,0xffff23,0xffff27,0xffff2b,0xffff2f,0xffff33,0xffff37,0xffff3b,0xffff3f,
  0xffff43,0xffff47,0xffff4b,0xffff4f,0xffff53,0xffff57,0xffff5b,0xffff5f,0xffff63,0xffff67,0xffff6b,0xffff6f,0xffff73,0xffff77,0xffff7b,0xffff7f,
  0xffff83,0xffff87,0xffff8b,0xffff8f,0xffff93,0xffff97,0xffff9b,0xffff9f,0xffffa3,0xffffa7,0xffffab,0xffffaf,0xffffb3,0xffffb7,0xffffbb,0xffffbf,
  0xffffc3,0xffffc7,0xffffcb,0xffffcf,0xffffd3,0xffffd7,0xffffdb,0xffffdf,0xffffe3,0xffffe7,0xffffeb,0xffffef,0xfffff3,0xfffff7,0xfffffb,0xffffff,
};

uint32 ColorMap::redLUT[256] = {
  0x00000,0x10000,0x20000,0x30000,0x40000,0x50000,0x60000,0x70000,0x80000,0x90000,0xa0000,0xb0000,0xc0000,0xd0000,0xe0000,0xf0000,
  0x100000,0x110000,0x120000,0x130000,0x140000,0x150000,0x160000,0x170000,0x180000,0x190000,0x1a0000,0x1b0000,0x1c0000,0x1d0000,0x1e0000,0x1f0000,
  0x200000,0x210000,0x220000,0x230000,0x240000,0x250000,0x260000,0x270000,0x280000,0x290000,0x2a0000,0x2b0000,0x2c0000,0x2d0000,0x2e0000,0x2f0000,
  0x300000,0x310000,0x320000,0x330000,0x340000,0x350000,0x360000,0x370000,0x380000,0x390000,0x3a0000,0x3b0000,0x3c0000,0x3d0000,0x3e0000,0x3f0000,
  0x400000,0x410000,0x420000,0x430000,0x440000,0x450000,0x460000,0x470000,0x480000,0x490000,0x4a0000,0x4b0000,0x4c0000,0x4d0000,0x4e0000,0x4f0000,
  0x500000,0x510000,0x520000,0x530000,0x540000,0x550000,0x560000,0x570000,0x580000,0x590000,0x5a0000,0x5b0000,0x5c0000,0x5d0000,0x5e0000,0x5f0000,
  0x600000,0x610000,0x620000,0x630000,0x640000,0x650000,0x660000,0x670000,0x680000,0x690000,0x6a0000,0x6b0000,0x6c0000,0x6d0000,0x6e0000,0x6f0000,
  0x700000,0x710000,0x720000,0x730000,0x740000,0x750000,0x760000,0x770000,0x780000,0x790000,0x7a0000,0x7b0000,0x7c0000,0x7d0000,0x7e0000,0x7f0000,
  0x800000,0x810000,0x820000,0x830000,0x840000,0x850000,0x860000,0x870000,0x880000,0x890000,0x8a0000,0x8b0000,0x8c0000,0x8d0000,0x8e0000,0x8f0000,
  0x900000,0x910000,0x920000,0x930000,0x940000,0x950000,0x960000,0x970000,0x980000,0x990000,0x9a0000,0x9b0000,0x9c0000,0x9d0000,0x9e0000,0x9f0000,
  0xa00000,0xa10000,0xa20000,0xa30000,0xa40000,0xa50000,0xa60000,0xa70000,0xa80000,0xa90000,0xaa0000,0xab0000,0xac0000,0xad0000,0xae0000,0xaf0000,
  0xb00000,0xb10000,0xb20000,0xb30000,0xb40000,0xb50000,0xb60000,0xb70000,0xb80000,0xb90000,0xba0000,0xbb0000,0xbc0000,0xbd0000,0xbe0000,0xbf0000,
  0xc00000,0xc10000,0xc20000,0xc30000,0xc40000,0xc50000,0xc60000,0xc70000,0xc80000,0xc90000,0xca0000,0xcb0000,0xcc0000,0xcd0000,0xce0000,0xcf0000,
  0xd00000,0xd10000,0xd20000,0xd30000,0xd40000,0xd50000,0xd60000,0xd70000,0xd80000,0xd90000,0xda0000,0xdb0000,0xdc0000,0xdd0000,0xde0000,0xdf0000,
  0xe00000,0xe10000,0xe20000,0xe30000,0xe40000,0xe50000,0xe60000,0xe70000,0xe80000,0xe90000,0xea0000,0xeb0000,0xec0000,0xed0000,0xee0000,0xef0000,
  0xf00000,0xf10000,0xf20000,0xf30000,0xf40000,0xf50000,0xf60000,0xf70000,0xf80000,0xf90000,0xfa0000,0xfb0000,0xfc0000,0xfd0000,0xfe0000,0xff0000,
};

uint32 ColorMap::greenLUT[256] = {
  0x00000,0x00100,0x00200,0x00300,0x00400,0x00500,0x00600,0x00700,0x00800,0x00900,0x00a00,0x00b00,0x00c00,0x00d00,0x00e00,0x00f00,
  0x001000,0x001100,0x001200,0x001300,0x001400,0x001500,0x001600,0x001700,0x001800,0x001900,0x001a00,0x001b00,0x001c00,0x001d00,0x001e00,0x001f00,
  0x002000,0x002100,0x002200,0x002300,0x002400,0x002500,0x002600,0x002700,0x002800,0x002900,0x002a00,0x002b00,0x002c00,0x002d00,0x002e00,0x002f00,
  0x003000,0x003100,0x003200,0x003300,0x003400,0x003500,0x003600,0x003700,0x003800,0x003900,0x003a00,0x003b00,0x003c00,0x003d00,0x003e00,0x003f00,
  0x004000,0x004100,0x004200,0x004300,0x004400,0x004500,0x004600,0x004700,0x004800,0x004900,0x004a00,0x004b00,0x004c00,0x004d00,0x004e00,0x004f00,
  0x005000,0x005100,0x005200,0x005300,0x005400,0x005500,0x005600,0x005700,0x005800,0x005900,0x005a00,0x005b00,0x005c00,0x005d00,0x005e00,0x005f00,
  0x006000,0x006100,0x006200,0x006300,0x006400,0x006500,0x006600,0x006700,0x006800,0x006900,0x006a00,0x006b00,0x006c00,0x006d00,0x006e00,0x006f00,
  0x007000,0x007100,0x007200,0x007300,0x007400,0x007500,0x007600,0x007700,0x007800,0x007900,0x007a00,0x007b00,0x007c00,0x007d00,0x007e00,0x007f00,
  0x008000,0x008100,0x008200,0x008300,0x008400,0x008500,0x008600,0x008700,0x008800,0x008900,0x008a00,0x008b00,0x008c00,0x008d00,0x008e00,0x008f00,
  0x009000,0x009100,0x009200,0x009300,0x009400,0x009500,0x009600,0x009700,0x009800,0x009900,0x009a00,0x009b00,0x009c00,0x009d00,0x009e00,0x009f00,
  0x00a000,0x00a100,0x00a200,0x00a300,0x00a400,0x00a500,0x00a600,0x00a700,0x00a800,0x00a900,0x00aa00,0x00ab00,0x00ac00,0x00ad00,0x00ae00,0x00af00,
  0x00b000,0x00b100,0x00b200,0x00b300,0x00b400,0x00b500,0x00b600,0x00b700,0x00b800,0x00b900,0x00ba00,0x00bb00,0x00bc00,0x00bd00,0x00be00,0x00bf00,
  0x00c000,0x00c100,0x00c200,0x00c300,0x00c400,0x00c500,0x00c600,0x00c700,0x00c800,0x00c900,0x00ca00,0x00cb00,0x00cc00,0x00cd00,0x00ce00,0x00cf00,
  0x00d000,0x00d100,0x00d200,0x00d300,0x00d400,0x00d500,0x00d600,0x00d700,0x00d800,0x00d900,0x00da00,0x00db00,0x00dc00,0x00dd00,0x00de00,0x00df00,
  0x00e000,0x00e100,0x00e200,0x00e300,0x00e400,0x00e500,0x00e600,0x00e700,0x00e800,0x00e900,0x00ea00,0x00eb00,0x00ec00,0x00ed00,0x00ee00,0x00ef00,
  0x00f000,0x00f100,0x00f200,0x00f300,0x00f400,0x00f500,0x00f600,0x00f700,0x00f800,0x00f900,0x00fa00,0x00fb00,0x00fc00,0x00fd00,0x00fe00,0x00ff00,
};

uint32 ColorMap::blueLUT[256] = {
  0x00000,0x00001,0x00002,0x00003,0x00004,0x00005,0x00006,0x00007,0x00008,0x00009,0x0000a,0x0000b,0x0000c,0x0000d,0x0000e,0x0000f,
  0x000010,0x000011,0x000012,0x000013,0x000014,0x000015,0x000016,0x000017,0x000018,0x000019,0x00001a,0x00001b,0x00001c,0x00001d,0x00001e,0x00001f,
  0x000020,0x000021,0x000022,0x000023,0x000024,0x000025,0x000026,0x000027,0x000028,0x000029,0x00002a,0x00002b,0x00002c,0x00002d,0x00002e,0x00002f,
  0x000030,0x000031,0x000032,0x000033,0x000034,0x000035,0x000036,0x000037,0x000038,0x000039,0x00003a,0x00003b,0x00003c,0x00003d,0x00003e,0x00003f,
  0x000040,0x000041,0x000042,0x000043,0x000044,0x000045,0x000046,0x000047,0x000048,0x000049,0x00004a,0x00004b,0x00004c,0x00004d,0x00004e,0x00004f,
  0x000050,0x000051,0x000052,0x000053,0x000054,0x000055,0x000056,0x000057,0x000058,0x000059,0x00005a,0x00005b,0x00005c,0x00005d,0x00005e,0x00005f,
  0x000060,0x000061,0x000062,0x000063,0x000064,0x000065,0x000066,0x000067,0x000068,0x000069,0x00006a,0x00006b,0x00006c,0x00006d,0x00006e,0x00006f,
  0x000070,0x000071,0x000072,0x000073,0x000074,0x000075,0x000076,0x000077,0x000078,0x000079,0x00007a,0x00007b,0x00007c,0x00007d,0x00007e,0x00007f,
  0x000080,0x000081,0x000082,0x000083,0x000084,0x000085,0x000086,0x000087,0x000088,0x000089,0x00008a,0x00008b,0x00008c,0x00008d,0x00008e,0x00008f,
  0x000090,0x000091,0x000092,0x000093,0x000094,0x000095,0x000096,0x000097,0x000098,0x000099,0x00009a,0x00009b,0x00009c,0x00009d,0x00009e,0x00009f,
  0x0000a0,0x0000a1,0x0000a2,0x0000a3,0x0000a4,0x0000a5,0x0000a6,0x0000a7,0x0000a8,0x0000a9,0x0000aa,0x0000ab,0x0000ac,0x0000ad,0x0000ae,0x0000af,
  0x0000b0,0x0000b1,0x0000b2,0x0000b3,0x0000b4,0x0000b5,0x0000b6,0x0000b7,0x0000b8,0x0000b9,0x0000ba,0x0000bb,0x0000bc,0x0000bd,0x0000be,0x0000bf,
  0x0000c0,0x0000c1,0x0000c2,0x0000c3,0x0000c4,0x0000c5,0x0000c6,0x0000c7,0x0000c8,0x0000c9,0x0000ca,0x0000cb,0x0000cc,0x0000cd,0x0000ce,0x0000cf,
  0x0000d0,0x0000d1,0x0000d2,0x0000d3,0x0000d4,0x0000d5,0x0000d6,0x0000d7,0x0000d8,0x0000d9,0x0000da,0x0000db,0x0000dc,0x0000dd,0x0000de,0x0000df,
  0x0000e0,0x0000e1,0x0000e2,0x0000e3,0x0000e4,0x0000e5,0x0000e6,0x0000e7,0x0000e8,0x0000e9,0x0000ea,0x0000eb,0x0000ec,0x0000ed,0x0000ee,0x0000ef,
  0x0000f0,0x0000f1,0x0000f2,0x0000f3,0x0000f4,0x0000f5,0x0000f6,0x0000f7,0x0000f8,0x0000f9,0x0000fa,0x0000fb,0x0000fc,0x0000fd,0x0000fe,0x0000ff,
};

uint32 ColorMap::prismLUT[256] = {
  0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,
  0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,
  0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,
  0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,
  0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,
  0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,
  0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,
  0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,
  0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,
  0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,
  0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,
  0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,
  0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,
  0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,
  0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,
  0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,0xff,0xaa00ff,0xff0000,0xff7f00,0xffff00,0xff00,
};

uint32 ColorMap::boneLUT[256] = {
  0x0,0x1,0x10102,0x20203,0x30305,0x40406,0x50507,0x60608,0x70709,0x7070b,0x8080c,0x9090d,0xa0a0e,0xb0b10,0xc0c11,0xd0d12,
  0xe0e13,0xe0e14,0xf0f16,0x101017,0x111118,0x121219,0x13131a,0x14141c,0x15151d,0x15151e,0x16161f,0x171720,0x181822,0x191923,0x1a1a24,0x1b1b25,
  0x1c1c26,0x1c1c28,0x1d1d29,0x1e1e2a,0x1f1f2b,0x20202c,0x21212e,0x22222f,0x232330,0x232331,0x242433,0x252534,0x262635,0x272736,0x282837,0x292939,
  0x2a2a3a,0x2a2a3b,0x2b2b3c,0x2c2c3d,0x2d2d3f,0x2e2e40,0x2f2f41,0x303042,0x303043,0x313145,0x323246,0x333347,0x343448,0x353549,0x36364b,0x37374c,
  0x38384d,0x38384e,0x39394f,0x3a3a51,0x3b3b52,0x3c3c53,0x3d3d54,0x3e3e56,0x3f3f57,0x3f3f58,0x404059,0x41415a,0x42425c,0x43435d,0x44445e,0x45455f,
  0x464660,0x464662,0x474763,0x484864,0x494965,0x4a4a66,0x4b4b68,0x4c4c69,0x4d4d6a,0x4d4d6b,0x4e4e6c,0x4f4f6e,0x50506f,0x515170,0x525271,0x535373,
  0x545473,0x545574,0x555675,0x565776,0x575977,0x585a78,0x595b79,0x5a5c7a,0x5b5d7a,0x5b5f7b,0x5c607c,0x5d617d,0x5e627e,0x5f647f,0x606580,0x616681,
  0x616781,0x626882,0x636a83,0x646b84,0x656c85,0x666d86,0x676e87,0x687088,0x697188,0x697289,0x6a738a,0x6b748b,0x6c768c,0x6d778d,0x6e788e,0x6f798f,
  0x707a8f,0x707c90,0x717d91,0x727e92,0x737f93,0x748094,0x758295,0x768396,0x778496,0x778597,0x788798,0x798899,0x7a899a,0x7b8a9b,0x7c8b9c,0x7d8d9d,
  0x7e8e9d,0x7e8f9e,0x7f909f,0x8091a0,0x8193a1,0x8294a2,0x8395a3,0x8496a4,0x8597a4,0x8599a5,0x869aa6,0x879ba7,0x889ca8,0x899da9,0x8a9faa,0x8ba0ab,
  0x8ca1ab,0x8ca2ac,0x8da3ad,0x8ea5ae,0x8fa6af,0x90a7b0,0x91a8b1,0x92aab2,0x93abb2,0x93acb3,0x94adb4,0x95aeb5,0x96b0b6,0x97b1b7,0x98b2b8,0x99b3b9,
  0x9ab4b9,0x9ab6ba,0x9bb7bb,0x9cb8bc,0x9db9bd,0x9ebabe,0x9fbcbf,0xa0bdc0,0xa1bec0,0xa1bfc1,0xa2c0c2,0xa3c2c3,0xa4c3c4,0xa5c4c5,0xa6c5c6,0xa7c7c7,
  0xa8c7c7,0xa9c8c8,0xabc9c9,0xaccaca,0xadcbcb,0xafcccc,0xb0cdcd,0xb2cece,0xb3cece,0xb4cfcf,0xb6d0d0,0xb7d1d1,0xb8d2d2,0xbad3d3,0xbbd4d4,0xbdd5d5,
  0xbed5d5,0xbfd6d6,0xc1d7d7,0xc2d8d8,0xc3d9d9,0xc5dada,0xc6dbdb,0xc8dcdc,0xc9dcdc,0xcadddd,0xccdede,0xcddfdf,0xcee0e0,0xd0e1e1,0xd1e2e2,0xd3e3e3,
  0xd4e3e3,0xd5e4e4,0xd7e5e5,0xd8e6e6,0xd9e7e7,0xdbe8e8,0xdce9e9,0xdeeaea,0xdfeaea,0xe0ebeb,0xe2ecec,0xe3eded,0xe4eeee,0xe6efef,0xe7f0f0,0xe9f1f1,
  0xeaf1f1,0xebf2f2,0xedf3f3,0xeef4f4,0xeff5f5,0xf1f6f6,0xf2f7f7,0xf4f8f8,0xf5f8f8,0xf6f9f9,0xf8fafa,0xf9fbfb,0xfafcfc,0xfcfdfd,0xfdfefe,0xffffff,
};

uint32 ColorMap::jetLUT[256] = {
  0x83,0x87,0x8b,0x8f,0x93,0x97,0x9b,0x9f,0xa3,0xa7,0xab,0xaf,0xb3,0xb7,0xbb,0xbf,
  0xc3,0xc7,0xcb,0xcf,0xd3,0xd7,0xdb,0xdf,0xe3,0xe7,0xeb,0xef,0xf3,0xf7,0xfb,0xff,
  0x3ff,0x7ff,0xbff,0xfff,0x13ff,0x17ff,0x1bff,0x1fff,0x23ff,0x27ff,0x2bff,0x2fff,0x33ff,0x37ff,0x3bff,0x3fff,
  0x43ff,0x47ff,0x4bff,0x4fff,0x53ff,0x57ff,0x5bff,0x5fff,0x63ff,0x67ff,0x6bff,0x6fff,0x73ff,0x77ff,0x7bff,0x7fff,
  0x83ff,0x87ff,0x8bff,0x8fff,0x93ff,0x97ff,0x9bff,0x9fff,0xa3ff,0xa7ff,0xabff,0xafff,0xb3ff,0xb7ff,0xbbff,0xbfff,
  0xc3ff,0xc7ff,0xcbff,0xcfff,0xd3ff,0xd7ff,0xdbff,0xdfff,0xe3ff,0xe7ff,0xebff,0xefff,0xf3ff,0xf7ff,0xfbff,0xffff,
  0x3fffb,0x7fff7,0xbfff3,0xfffef,0x13ffeb,0x17ffe7,0x1bffe3,0x1fffdf,0x23ffdb,0x27ffd7,0x2bffd3,0x2fffcf,0x33ffcb,0x37ffc7,0x3bffc3,0x3fffbf,
  0x43ffbb,0x47ffb7,0x4bffb3,0x4fffaf,0x53ffab,0x57ffa7,0x5bffa3,0x5fff9f,0x63ff9b,0x67ff97,0x6bff93,0x6fff8f,0x73ff8b,0x77ff87,0x7bff83,0x7fff7f,
  0x83ff7b,0x87ff77,0x8bff73,0x8fff6f,0x93ff6b,0x97ff67,0x9bff63,0x9fff5f,0xa3ff5b,0xa7ff57,0xabff53,0xafff4f,0xb3ff4b,0xb7ff47,0xbbff43,0xbfff3f,
  0xc3ff3b,0xc7ff37,0xcbff33,0xcfff2f,0xd3ff2b,0xd7ff27,0xdbff23,0xdfff1f,0xe3ff1b,0xe7ff17,0xebff13,0xefff0f,0xf3ff0b,0xf7ff07,0xfbff03,0xffff00,
  0xfffb00,0xfff700,0xfff300,0xffef00,0xffeb00,0xffe700,0xffe300,0xffdf00,0xffdb00,0xffd700,0xffd300,0xffcf00,0xffcb00,0xffc700,0xffc300,0xffbf00,
  0xffbb00,0xffb700,0xffb300,0xffaf00,0xffab00,0xffa700,0xffa300,0xff9f00,0xff9b00,0xff9700,0xff9300,0xff8f00,0xff8b00,0xff8700,0xff8300,0xff7f00,
  0xff7b00,0xff7700,0xff7300,0xff6f00,0xff6b00,0xff6700,0xff6300,0xff5f00,0xff5b00,0xff5700,0xff5300,0xff4f00,0xff4b00,0xff4700,0xff4300,0xff3f00,
  0xff3b00,0xff3700,0xff3300,0xff2f00,0xff2b00,0xff2700,0xff2300,0xff1f00,0xff1b00,0xff1700,0xff1300,0xff0f00,0xff0b00,0xff0700,0xff0300,0xff0000,
  0xfb0000,0xf70000,0xf30000,0xef0000,0xeb0000,0xe70000,0xe30000,0xdf0000,0xdb0000,0xd70000,0xd30000,0xcf0000,0xcb0000,0xc70000,0xc30000,0xbf0000,
  0xbb0000,0xb70000,0xb30000,0xaf0000,0xab0000,0xa70000,0xa30000,0x9f0000,0x9b0000,0x970000,0x930000,0x8f0000,0x8b0000,0x870000,0x830000,0x7f0000,
};

