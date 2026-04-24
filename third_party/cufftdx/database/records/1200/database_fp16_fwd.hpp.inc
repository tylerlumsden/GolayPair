//Copyright (c) 2019-2026, NVIDIA CORPORATION & AFFILIATES. All rights reserved.
//
//NVIDIA CORPORATION and its licensors retain all intellectual property
//and proprietary rights in and to this software, related documentation
//and any modifications thereto.  Any use, reproduction, disclosure or
//distribution of this software and related documentation without an express
//license agreement from NVIDIA CORPORATION is strictly prohibited.
//


template<> struct block_fft_record<33, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<33,   33,   33,    1,  1024,     0,    0,   959>
    >;
};

template<> struct block_fft_record<34, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<34,   34,   34,    1,  1024,     0,    0,   960>
    >;
};

template<> struct block_fft_record<35, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<35,   35,   35,    1,  1024,     0,    0,   961>
    >;
};

template<> struct block_fft_record<37, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<37,   37,   37,    1,  1024,     0,    0,   962>
    >;
};

template<> struct block_fft_record<38, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<38,   38,   38,    1,   768,     0,    0,   963>
    >;
};

template<> struct block_fft_record<39, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<39,   39,   39,    1,  1024,     0,    0,   964>
    >;
};

template<> struct block_fft_record<40, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<20,    2,   20,    2,    32,    80,    4,   965>,
        block_fft_implementation<20,    2,   20,    2,    32,   160,    2,   966>,
        block_fft_implementation<10,    2,   10,    4,    32,   160,    4,   967>,
        block_fft_implementation<40,   40,   40,    1,  1024,     0,    0,   968>
    >;
};

template<> struct block_fft_record<41, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<41,   41,   41,    1,   768,     0,    0,   969>
    >;
};

template<> struct block_fft_record<42, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<42,   42,   42,    1,  1024,     0,    0,   970>
    >;
};

template<> struct block_fft_record<43, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<43,   43,   43,    1,   512,     0,    0,   971>
    >;
};

template<> struct block_fft_record<44, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<44,   44,   44,    1,   512,     0,    0,   972>
    >;
};

template<> struct block_fft_record<45, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<45,   45,   45,    1,  1024,     0,    0,   973>
    >;
};

template<> struct block_fft_record<46, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<46,   46,   46,    1,   768,     0,    0,   974>
    >;
};

template<> struct block_fft_record<47, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<47,   47,   47,    1,   128,     0,    0,   975>
    >;
};

template<> struct block_fft_record<48, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<48,   48,   48,    1,  1024,     0,    0,   976>
    >;
};

template<> struct block_fft_record<50, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<50,   50,   50,    1,   768,     0,    0,   977>
    >;
};

template<> struct block_fft_record<51, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<51,   51,   51,    1,   512,     0,    0,   978>
    >;
};

template<> struct block_fft_record<52, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<52,   52,   52,    1,   768,     0,    0,   979>
    >;
};

template<> struct block_fft_record<53, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<53,   53,   53,    1,   768,     0,    0,   980>
    >;
};

template<> struct block_fft_record<54, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<54,   54,   54,    1,   512,     0,    0,   981>
    >;
};

template<> struct block_fft_record<55, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<55,   55,   55,    1,   512,     0,    0,   982>
    >;
};

template<> struct block_fft_record<56, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<56,   56,   56,    1,   384,     0,    0,   983>
    >;
};

template<> struct block_fft_record<57, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<57,   57,   57,    1,   512,     0,    0,   984>
    >;
};

template<> struct block_fft_record<58, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<58,   58,   58,    1,   512,     0,    0,   985>
    >;
};

template<> struct block_fft_record<59, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<59,   59,   59,    1,    64,     0,    0,   986>
    >;
};

template<> struct block_fft_record<60, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<60,   60,   60,    1,   768,     0,    0,   987>
    >;
};

template<> struct block_fft_record<61, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<61,   61,   61,    1,   512,     0,    0,   988>
    >;
};

template<> struct block_fft_record<62, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<62,   62,   62,    1,    64,     0,    0,   989>
    >;
};

template<> struct block_fft_record<63, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<63,   63,   63,    1,   512,     0,    0,   990>
    >;
};

template<> struct block_fft_record<2, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 2,    2,    2,    1,   128,     0,    0,   991>
    >;
};

template<> struct block_fft_record<4, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 4,    4,    4,    1,   640,     0,    0,   992>,
        block_fft_implementation< 2,    2,    2,    2,   768,     8,    4,   993>,
        block_fft_implementation< 2,    2,    2,    2,   768,    16,    2,   994>
    >;
};

template<> struct block_fft_record<8, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 8,    8,    8,    1,    64,     0,    0,   995>,
        block_fft_implementation< 4,    2,    4,    2,   384,    16,    4,   996>,
        block_fft_implementation< 4,    2,    4,    2,   768,    32,    2,   997>,
        block_fft_implementation< 2,    2,    2,    4,   384,    16,    8,   998>,
        block_fft_implementation< 2,    2,    2,    4,   384,    32,    4,   999>
    >;
};

template<> struct block_fft_record<16, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<16,   16,   16,    1,   896,     0,    0,  1000>,
        block_fft_implementation< 4,    4,    4,    4,   192,    32,    4,  1001>,
        block_fft_implementation< 4,    4,    4,    4,   192,    64,    2,  1002>,
        block_fft_implementation< 8,    2,    8,    2,   128,    32,    4,  1003>,
        block_fft_implementation< 2,    2,    2,    8,   160,    32,   12,  1005>,
        block_fft_implementation< 8,    2,    8,    2,   832,    64,    2,  1004>,
        block_fft_implementation< 2,    2,    2,    8,   192,    64,    6,  1006>
    >;
};

template<> struct block_fft_record<32, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<32,   32,   32,    1,  1024,     0,    0,  1007>,
        block_fft_implementation< 8,    4,    8,    4,   128,   128,    2,  1008>,
        block_fft_implementation< 8,    4,    8,    4,    64,    64,    4,  1009>,
        block_fft_implementation< 4,    2,    4,    8,    96,   128,    4,  1010>,
        block_fft_implementation< 4,    2,    4,    8,    96,    64,    8,  1011>,
        block_fft_implementation< 2,    2,    2,   16,    96,    64,   16,  1014>,
        block_fft_implementation< 2,    2,    2,   16,    64,   128,    8,  1013>,
        block_fft_implementation<16,    2,   16,    2,    60,   128,    2,  1012>,
        block_fft_implementation<16,    2,   16,    2,    62,    64,    4,  1015>
    >;
};

template<> struct block_fft_record<64, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 8,    8,    8,    8,    32,   256,    2,  1017>,
        block_fft_implementation< 8,    8,    8,    8,    30,   128,    4,  1016>,
        block_fft_implementation< 4,    4,    4,   16,    48,   256,    4,  1018>,
        block_fft_implementation< 4,    4,    4,   16,    32,   128,    8,  1019>,
        block_fft_implementation<16,    4,   16,    4,    32,   128,    4,  1021>,
        block_fft_implementation<16,    4,   16,    4,    60,   256,    2,  1020>,
        block_fft_implementation<32,    2,   32,    2,    58,   256,    2,  1022>,
        block_fft_implementation< 2,    2,    2,   32,    32,   256,   10,  1024>,
        block_fft_implementation< 2,    2,    2,   32,    46,   128,   20,  1023>,
        block_fft_implementation<32,    2,   32,    2,    62,   128,    4,  1025>,
        block_fft_implementation<64,   64,   64,    1,   512,     0,    0,  1026>
    >;
};

template<> struct block_fft_record<128, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<16,    8,   16,    8,    16,   256,    4,  1027>,
        block_fft_implementation< 8,    2,    8,   16,    16,   512,    4,  1028>,
        block_fft_implementation< 8,    2,    8,   16,    16,   256,    8,  1030>,
        block_fft_implementation<16,    8,   16,    8,    16,   512,    2,  1029>,
        block_fft_implementation< 4,    2,    4,   32,    16,   512,    6,  1031>,
        block_fft_implementation<32,    4,   32,    4,    30,   512,    2,  1033>,
        block_fft_implementation< 4,    2,    4,   32,    12,   256,   12,  1032>,
        block_fft_implementation<32,    4,   32,    4,    32,   256,    4,  1034>,
        block_fft_implementation< 2,    2,    2,   64,    16,   512,   12,  1036>,
        block_fft_implementation< 2,    2,    2,   64,    20,   256,   24,  1035>
    >;
};

template<> struct block_fft_record<256, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<16,   16,   16,   16,     8,   512,    4,  1037>,
        block_fft_implementation< 8,    4,    8,   32,     8,  1024,    4,  1038>,
        block_fft_implementation< 8,    4,    8,   32,     4,   512,    8,  1039>,
        block_fft_implementation<16,   16,   16,   16,     8,  1024,    2,  1040>,
        block_fft_implementation< 4,    4,    4,   64,     8,  1024,    6,  1041>,
        block_fft_implementation<32,    8,   32,    8,    32,  1024,    2,  1042>,
        block_fft_implementation<32,    8,   32,    8,    16,   512,    4,  1044>,
        block_fft_implementation< 4,    4,    4,   64,     6,   512,   12,  1043>,
        block_fft_implementation< 2,    2,    2,  128,    12,  1024,   14,  1046>,
        block_fft_implementation< 2,    2,    2,  128,    12,   512,   28,  1045>
    >;
};

template<> struct block_fft_record<512, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 8,    8,    8,   64,     2,  2048,    4,  1047>,
        block_fft_implementation< 8,    8,    8,   64,     2,  1024,    8,  1048>,
        block_fft_implementation<16,    2,   16,   32,     4,  1024,    8,  1049>,
        block_fft_implementation<32,   16,   32,   16,     8,  1024,    4,  1051>,
        block_fft_implementation<32,   16,   32,   16,    16,  2048,    2,  1050>,
        block_fft_implementation< 4,    2,    4,  128,     2,  2048,    8,  1053>,
        block_fft_implementation<16,    2,   16,   32,     8,  2048,    4,  1052>,
        block_fft_implementation< 4,    2,    4,  128,     4,  1024,   16,  1054>,
        block_fft_implementation< 2,    2,    2,  256,     4,  2048,   16,  1056>,
        block_fft_implementation< 2,    2,    2,  256,     6,  1024,   32,  1055>
    >;
};

template<> struct block_fft_record<1024, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<16,    4,   16,   64,     2,  2048,    8,  1057>,
        block_fft_implementation< 8,    2,    8,  128,     2,  4096,    6,  1059>,
        block_fft_implementation<32,   32,   32,   32,     2,  2048,    4,  1058>,
        block_fft_implementation<32,   32,   32,   32,     8,  4096,    2,  1060>,
        block_fft_implementation<16,    4,   16,   64,     2,  4096,    4,  1062>,
        block_fft_implementation< 4,    4,    4,  256,     2,  4096,    8,  1063>,
        block_fft_implementation< 8,    2,    8,  128,     2,  2048,   12,  1061>,
        block_fft_implementation< 4,    4,    4,  256,     2,  2048,   16,  1064>,
        block_fft_implementation< 2,    2,    2,  512,     2,  4096,   18,  1066>,
        block_fft_implementation< 2,    2,    2,  512,     4,  2048,   36,  1065>
    >;
};

template<> struct block_fft_record<2048, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<16,    8,   16,  128,     2,  4096,    8,  1067>,
        block_fft_implementation< 8,    4,    8,  256,     2,  8192,    6,  1068>,
        block_fft_implementation<16,    8,   16,  128,     2,  8192,    4,  1071>,
        block_fft_implementation<32,    2,   32,   64,     4,  8192,    4,  1072>,
        block_fft_implementation< 8,    4,    8,  256,     2,  4096,   12,  1069>,
        block_fft_implementation< 4,    2,    4,  512,     2,  8192,   10,  1073>,
        block_fft_implementation<32,    2,   32,   64,     2,  4096,    8,  1070>,
        block_fft_implementation< 4,    2,    4,  512,     2,  4096,   20,  1074>,
        block_fft_implementation< 2,    2,    2, 1024,     2,  8192,   20,  1076>,
        block_fft_implementation< 2,    2,    2, 1024,     2,  4096,   40,  1075>
    >;
};

template<> struct block_fft_record<4096, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 8,    8,    8,  512,     2, 16384,    6,  1078>,
        block_fft_implementation<16,   16,   16,  256,     2,  8192,    8,  1077>,
        block_fft_implementation<16,   16,   16,  256,     2, 16384,    4,  1081>,
        block_fft_implementation<32,    4,   32,  128,     2, 16384,    4,  1082>,
        block_fft_implementation<32,    4,   32,  128,     2,  8192,    8,  1080>,
        block_fft_implementation< 8,    8,    8,  512,     2,  8192,   12,  1079>,
        block_fft_implementation< 4,    4,    4, 1024,     2, 16384,   10,  1083>,
        block_fft_implementation< 4,    4,    4, 1024,     2,  8192,   20,  1084>
    >;
};

template<> struct block_fft_record<8192, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<32,    8,   32,  256,     2, 32768,    4,  1087>,
        block_fft_implementation< 8,    2,    8, 1024,     2, 32768,    8,  1086>,
        block_fft_implementation<16,    2,   16,  512,     2, 32768,    6,  1090>,
        block_fft_implementation<32,    8,   32,  256,     2, 16384,    8,  1088>,
        block_fft_implementation<16,    2,   16,  512,     2, 16384,   12,  1085>,
        block_fft_implementation< 8,    2,    8, 1024,     2, 16384,   16,  1089>
    >;
};

template<> struct block_fft_record<16384, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<32,   16,   32,  512,     2, 32768,    8,  1092>,
        block_fft_implementation<16,    4,   16, 1024,     2, 32768,   12,  1091>
    >;
};

template<> struct block_fft_record<3, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 3,    3,    3,    1,   768,     0,    0,  1093>
    >;
};

template<> struct block_fft_record<9, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 9,    9,    9,    1,   640,     0,    0,  1094>,
        block_fft_implementation< 3,    3,    3,    3,   160,    36,    2,  1095>,
        block_fft_implementation< 3,    3,    3,    3,   256,    18,    4,  1096>
    >;
};

template<> struct block_fft_record<27, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<27,   27,   27,    1,  1024,     0,    0,  1097>,
        block_fft_implementation< 9,    3,    9,    3,    42,   108,    2,  1098>,
        block_fft_implementation< 9,    3,    9,    3,    42,    54,    4,  1099>,
        block_fft_implementation< 3,    3,    3,    9,    56,   108,    4,  1100>,
        block_fft_implementation< 3,    3,    3,    9,    56,    54,    8,  1101>
    >;
};

template<> struct block_fft_record<81, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 9,    9,    9,    9,    14,   324,    2,  1103>,
        block_fft_implementation< 9,    9,    9,    9,    14,   162,    4,  1102>,
        block_fft_implementation<27,    3,   27,    3,    42,   162,    4,  1104>,
        block_fft_implementation<27,    3,   27,    3,    42,   324,    2,  1105>,
        block_fft_implementation< 3,    3,    3,   27,    36,   324,    6,  1106>,
        block_fft_implementation< 3,    3,    3,   27,    28,   162,   12,  1107>
    >;
};

template<> struct block_fft_record<243, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<27,    9,   27,    9,    14,   972,    2,  1108>,
        block_fft_implementation<27,    9,   27,    9,    14,   486,    4,  1109>,
        block_fft_implementation< 9,    3,    9,   27,    18,   972,    4,  1110>,
        block_fft_implementation< 9,    3,    9,   27,     2,   486,    8,  1111>,
        block_fft_implementation< 3,    3,    3,   81,     6,   972,    8,  1112>,
        block_fft_implementation< 3,    3,    3,   81,    18,   486,   16,  1113>
    >;
};

template<> struct block_fft_record<729, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<27,   27,   27,   27,    28,  2916,    2,  1114>,
        block_fft_implementation<27,   27,   27,   27,    18,  1458,    4,  1115>,
        block_fft_implementation< 9,    9,    9,   81,     6,  2916,    4,  1116>,
        block_fft_implementation< 9,    9,    9,   81,     6,  1458,    8,  1117>,
        block_fft_implementation< 3,    3,    3,  243,     2,  2916,   10,  1118>,
        block_fft_implementation< 3,    3,    3,  243,     6,  1458,   20,  1119>
    >;
};

template<> struct block_fft_record<2187, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<27,    3,   27,   81,     6,  8748,    4,  1120>,
        block_fft_implementation< 9,    3,    9,  243,     2,  8748,    6,  1122>,
        block_fft_implementation<27,    3,   27,   81,     6,  4374,    8,  1121>,
        block_fft_implementation< 9,    3,    9,  243,     2,  4374,   12,  1123>,
        block_fft_implementation< 3,    3,    3,  729,     2,  8748,   12,  1124>,
        block_fft_implementation< 3,    3,    3,  729,     2,  4374,   24,  1125>
    >;
};

template<> struct block_fft_record<6561, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<27,    9,   27,  243,     2, 26244,    4,  1126>,
        block_fft_implementation< 9,    9,    9,  729,     2, 26244,    6,  1128>,
        block_fft_implementation<27,    9,   27,  243,     2, 13122,    8,  1127>,
        block_fft_implementation< 9,    9,    9,  729,     2, 13122,   12,  1129>
    >;
};

template<> struct block_fft_record<19683, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<27,   27,   27,  729,     2, 39366,    8,  1511>
    >;
};

template<> struct block_fft_record<5, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 5,    5,    5,    1,  1024,     0,    0,  1130>
    >;
};

template<> struct block_fft_record<25, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<25,   25,   25,    1,  1024,     0,    0,  1131>,
        block_fft_implementation< 5,    5,    5,    5,    50,   100,    2,  1132>,
        block_fft_implementation< 5,    5,    5,    5,    50,    50,    4,  1133>
    >;
};

template<> struct block_fft_record<125, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 5,    5,    5,   25,    10,   500,    4,  1136>,
        block_fft_implementation<25,    5,   25,    5,    50,   500,    2,  1135>,
        block_fft_implementation<25,    5,   25,    5,    50,   250,    4,  1134>,
        block_fft_implementation< 5,    5,    5,   25,    10,   250,    8,  1137>
    >;
};

template<> struct block_fft_record<625, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<25,   25,   25,   25,    20,  2500,    2,  1138>,
        block_fft_implementation<25,   25,   25,   25,    10,  1250,    4,  1139>,
        block_fft_implementation< 5,    5,    5,  125,     2,  2500,    6,  1140>,
        block_fft_implementation< 5,    5,    5,  125,     2,  1250,   12,  1141>
    >;
};

template<> struct block_fft_record<3125, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<25,    5,   25,  125,     2, 12500,    4,  1142>,
        block_fft_implementation<25,    5,   25,  125,     2,  6250,    8,  1143>,
        block_fft_implementation< 5,    5,    5,  625,     2, 12500,    8,  1144>,
        block_fft_implementation< 5,    5,    5,  625,     2,  6250,   16,  1145>
    >;
};

template<> struct block_fft_record<15625, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<25,   25,   25,  625,     2, 31250,    8,  1146>
    >;
};

template<> struct block_fft_record<7, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 7,    7,    7,    1,  1024,     0,    0,  1147>
    >;
};

template<> struct block_fft_record<49, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 7,    7,    7,    7,    18,   196,    2,  1148>,
        block_fft_implementation< 7,    7,    7,    7,    18,    98,    4,  1149>,
        block_fft_implementation<49,   49,   49,    1,   768,     0,    0,  1150>
    >;
};

template<> struct block_fft_record<343, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 7,    7,    7,   49,    10,  1372,    4,  1151>,
        block_fft_implementation< 7,    7,    7,   49,    10,   686,    8,  1152>
    >;
};

template<> struct block_fft_record<2401, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 7,    7,    7,  343,     2,  9604,    6,  1153>,
        block_fft_implementation< 7,    7,    7,  343,     4,  4802,   12,  1154>
    >;
};

template<> struct block_fft_record<16807, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<49,    7,   49,  343,     2, 33614,    8,  1514>
    >;
};

template<> struct block_fft_record<11, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<11,   11,   11,    1,   896,     0,    0,  1155>
    >;
};

template<> struct block_fft_record<121, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<11,   11,   11,   11,    46,   484,    2,  1156>,
        block_fft_implementation<11,   11,   11,   11,    46,   242,    4,  1157>
    >;
};

template<> struct block_fft_record<1331, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<11,   11,   11,  121,     2,  5324,    4,  1158>,
        block_fft_implementation<11,   11,   11,  121,     2,  2662,    8,  1159>
    >;
};

template<> struct block_fft_record<6, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 6,    6,    6,    1,  1024,     0,    0,  1160>
    >;
};

template<> struct block_fft_record<36, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 6,    6,    6,    6,    42,   144,    2,  1161>,
        block_fft_implementation< 6,    6,    6,    6,    42,    72,    4,  1162>,
        block_fft_implementation<36,   36,   36,    1,  1024,     0,    0,  1163>
    >;
};

template<> struct block_fft_record<216, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 6,    6,    6,   36,    14,   864,    4,  1164>,
        block_fft_implementation<36,    6,   36,    6,    10,   432,    4,  1515>,
        block_fft_implementation<36,    6,   36,    6,    42,   864,    2,  1516>,
        block_fft_implementation< 6,    6,    6,   36,    14,   432,    8,  1165>
    >;
};

template<> struct block_fft_record<1296, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<36,   36,   36,   36,    14,  5184,    2,  1167>,
        block_fft_implementation<36,   36,   36,   36,    14,  2592,    4,  1166>,
        block_fft_implementation< 6,    6,    6,  216,     4,  5184,    6,  1168>,
        block_fft_implementation< 6,    6,    6,  216,     2,  2592,   12,  1169>
    >;
};

template<> struct block_fft_record<7776, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<36,    6,   36,  216,     2, 31104,    4,  1170>,
        block_fft_implementation<36,    6,   36,  216,     2, 15552,    8,  1171>
    >;
};

template<> struct block_fft_record<10, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<10,   10,   10,    1,  1024,     0,    0,  1172>
    >;
};

template<> struct block_fft_record<100, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<10,   10,   10,   10,    50,   400,    2,  1173>,
        block_fft_implementation<10,   10,   10,   10,    12,   200,    4,  1174>
    >;
};

template<> struct block_fft_record<1000, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<10,   10,   10,  100,    10,  4000,    4,  1175>,
        block_fft_implementation<10,   10,   10,  100,    10,  2000,    8,  1176>
    >;
};

template<> struct block_fft_record<10000, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<10,   10,   10, 1000,     2, 40000,    6,  1517>,
        block_fft_implementation<10,   10,   10, 1000,     2, 20000,   12,  1177>
    >;
};

template<> struct block_fft_record<12, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<12,   12,   12,    1,  1024,     0,    0,  1178>
    >;
};

template<> struct block_fft_record<144, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<12,   12,   12,   12,    42,   576,    2,  1180>,
        block_fft_implementation<12,   12,   12,   12,    42,   288,    4,  1179>
    >;
};

template<> struct block_fft_record<1728, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<12,   12,   12,  144,    12,  6912,    4,  1182>,
        block_fft_implementation<12,   12,   12,  144,     8,  3456,    8,  1181>
    >;
};

template<> struct block_fft_record<13, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<13,   13,   13,    1,  1024,     0,    0,  1183>
    >;
};

template<> struct block_fft_record<169, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<13,   13,   13,   13,    38,   676,    2,  1184>,
        block_fft_implementation<13,   13,   13,   13,    38,   338,    4,  1185>
    >;
};

template<> struct block_fft_record<2197, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<13,   13,   13,  169,     6,  8788,    4,  1186>,
        block_fft_implementation<13,   13,   13,  169,     6,  4394,    8,  1187>
    >;
};

template<> struct block_fft_record<14, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<14,   14,   14,    1,  1024,     0,    0,  1188>
    >;
};

template<> struct block_fft_record<196, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<14,   14,   14,   14,    18,   784,    2,  1189>,
        block_fft_implementation<14,   14,   14,   14,    18,   392,    4,  1190>
    >;
};

template<> struct block_fft_record<2744, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<14,   14,   14,  196,     6, 10976,    4,  1191>,
        block_fft_implementation<14,   14,   14,  196,    10,  5488,    8,  1192>
    >;
};

template<> struct block_fft_record<15, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<15,   15,   15,    1,  1024,     0,    0,  1193>
    >;
};

template<> struct block_fft_record<225, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<15,   15,   15,   15,    34,   900,    2,  1194>,
        block_fft_implementation<15,   15,   15,   15,     4,   450,    4,  1195>
    >;
};

template<> struct block_fft_record<3375, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<15,   15,   15,  225,     2, 13500,    4,  1196>,
        block_fft_implementation<15,   15,   15,  225,     2,  6750,    8,  1197>
    >;
};

template<> struct block_fft_record<17, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<17,   17,   17,    1,   896,     0,    0,  1198>
    >;
};

template<> struct block_fft_record<289, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<17,   17,   17,   17,    30,  1156,    2,  1199>,
        block_fft_implementation<17,   17,   17,   17,    30,   578,    4,  1200>
    >;
};

template<> struct block_fft_record<4913, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<17,   17,   17,  289,     4, 19652,    4,  1202>,
        block_fft_implementation<17,   17,   17,  289,     6,  9826,    8,  1201>
    >;
};

template<> struct block_fft_record<18, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<18,   18,   18,    1,  1024,     0,    0,  1203>
    >;
};

template<> struct block_fft_record<324, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<18,   18,   18,   18,    14,  1296,    2,  1205>,
        block_fft_implementation<18,   18,   18,   18,    14,   648,    4,  1204>
    >;
};

template<> struct block_fft_record<5832, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<18,   18,   18,  324,     2, 23328,    4,  1206>,
        block_fft_implementation<18,   18,   18,  324,     6, 11664,    8,  1207>
    >;
};

template<> struct block_fft_record<19, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<19,   19,   19,    1,  1024,     0,    0,  1208>
    >;
};

template<> struct block_fft_record<361, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<19,   19,   19,   19,    40,  1444,    2,  1209>,
        block_fft_implementation<19,   19,   19,   19,    26,   722,    4,  1210>
    >;
};

template<> struct block_fft_record<6859, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<19,   19,   19,  361,     2, 27436,    4,  1211>,
        block_fft_implementation<19,   19,   19,  361,     4, 13718,    8,  1212>
    >;
};

template<> struct block_fft_record<20, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<20,   20,   20,    1,   896,     0,    0,  1213>
    >;
};

template<> struct block_fft_record<400, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<20,   20,   20,   20,     6,   800,    4,  1214>,
        block_fft_implementation<20,   20,   20,   20,    12,  1600,    2,  1215>
    >;
};

template<> struct block_fft_record<8000, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<20,   20,   20,  400,     2, 32000,    4,  1216>,
        block_fft_implementation<20,   20,   20,  400,     4, 16000,    8,  1217>
    >;
};

template<> struct block_fft_record<21, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<21,   21,   21,    1,  1024,     0,    0,  1218>
    >;
};

template<> struct block_fft_record<441, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<21,   21,   21,   21,     6,  1764,    2,  1220>,
        block_fft_implementation<21,   21,   21,   21,     6,   882,    4,  1219>
    >;
};

template<> struct block_fft_record<9261, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<21,   21,   21,  441,     2, 37044,    4,  1518>,
        block_fft_implementation<21,   21,   21,  441,     4, 18522,    8,  1221>
    >;
};

template<> struct block_fft_record<22, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<22,   22,   22,    1,  1024,     0,    0,  1222>
    >;
};

template<> struct block_fft_record<484, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<22,   22,   22,   22,    46,  1936,    2,  1224>,
        block_fft_implementation<22,   22,   22,   22,    46,   968,    4,  1223>
    >;
};

template<> struct block_fft_record<10648, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<22,   22,   22,  484,     2, 42592,    4,  1519>,
        block_fft_implementation<22,   22,   22,  484,     2, 21296,    8,  1225>
    >;
};

template<> struct block_fft_record<23, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<23,   23,   23,    1,  1024,     0,    0,  1226>
    >;
};

template<> struct block_fft_record<529, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<23,   23,   23,   23,    22,  2116,    2,  1227>,
        block_fft_implementation<23,   23,   23,   23,    22,  1058,    4,  1228>
    >;
};

template<> struct block_fft_record<12167, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<23,   23,   23,  529,     2, 48668,    4,  1520>,
        block_fft_implementation<23,   23,   23,  529,     2, 24334,    8,  1229>
    >;
};

template<> struct block_fft_record<24, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<24,   24,   24,    1,  1024,     0,    0,  1230>
    >;
};

template<> struct block_fft_record<576, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<24,   24,   24,   24,    10,  2304,    2,  1232>,
        block_fft_implementation<24,   24,   24,   24,    10,  1152,    4,  1231>
    >;
};

template<> struct block_fft_record<13824, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<24,   24,   24,  576,     2, 27648,    8,  1233>
    >;
};

template<> struct block_fft_record<26, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<26,   26,   26,    1,  1024,     0,    0,  1234>
    >;
};

template<> struct block_fft_record<676, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<26,   26,   26,   26,    28,  2704,    2,  1236>,
        block_fft_implementation<26,   26,   26,   26,    38,  1352,    4,  1235>
    >;
};

template<> struct block_fft_record<17576, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<26,   26,   26,  676,     2, 35152,    8,  1523>
    >;
};

template<> struct block_fft_record<28, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<28,   28,   28,    1,  1024,     0,    0,  1237>
    >;
};

template<> struct block_fft_record<784, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<28,   28,   28,   28,    18,  1568,    4,  1238>,
        block_fft_implementation<28,   28,   28,   28,    18,  3136,    2,  1239>
    >;
};

template<> struct block_fft_record<21952, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<28,   28,   28,  784,     2, 43904,    8,  1524>
    >;
};

template<> struct block_fft_record<29, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<29,   29,   29,    1,  1024,     0,    0,  1240>
    >;
};

template<> struct block_fft_record<841, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<29,   29,   29,   29,    26,  3364,    2,  1242>,
        block_fft_implementation<29,   29,   29,   29,    26,  1682,    4,  1241>
    >;
};

template<> struct block_fft_record<24389, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<29,   29,   29,  841,     2, 48778,    8,  1525>
    >;
};

template<> struct block_fft_record<30, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<30,   30,   30,    1,  1024,     0,    0,  1243>
    >;
};

template<> struct block_fft_record<900, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<30,   30,   30,   30,     2,  3600,    2,  1245>,
        block_fft_implementation<30,   30,   30,   30,     2,  1800,    4,  1244>
    >;
};

template<> struct block_fft_record<31, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<31,   31,   31,    1,  1024,     0,    0,  1246>
    >;
};

template<> struct block_fft_record<961, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<31,   31,   31,   31,     4,  3844,    2,  1247>,
        block_fft_implementation<31,   31,   31,   31,     2,  1922,    4,  1248>
    >;
};

template<> struct block_fft_record<68, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<34,    2,   34,    2,    32,   136,    4,  1249>,
        block_fft_implementation<34,    2,   34,    2,   128,   272,    2,  1250>
    >;
};

template<> struct block_fft_record<72, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<12,    6,   12,    6,    42,   288,    2,  1252>,
        block_fft_implementation<12,    6,   12,    6,    42,   144,    4,  1251>,
        block_fft_implementation<36,    2,   36,    2,    32,   144,    4,  1253>,
        block_fft_implementation<24,    3,   24,    3,    20,   144,    4,  1254>,
        block_fft_implementation< 6,    2,    6,   12,    42,   288,    4,  1259>,
        block_fft_implementation<24,    3,   24,    3,    40,   288,    2,  1256>,
        block_fft_implementation< 6,    2,    6,   12,    16,   144,    8,  1260>,
        block_fft_implementation<36,    2,   36,    2,    32,   288,    2,  1255>,
        block_fft_implementation<18,    2,   18,    4,    32,   288,    4,  1258>,
        block_fft_implementation<18,    2,   18,    4,    16,   144,    8,  1257>
    >;
};

template<> struct block_fft_record<76, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<38,    2,   38,    2,    32,   152,    4,  1261>,
        block_fft_implementation<38,    2,   38,    2,   128,   304,    2,  1262>
    >;
};

template<> struct block_fft_record<80, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<20,    4,   20,    4,    16,   160,    4,  1263>,
        block_fft_implementation<20,    4,   20,    4,    16,   320,    2,  1264>,
        block_fft_implementation<40,    2,   40,    2,    32,   160,    4,  1265>,
        block_fft_implementation<40,    2,   40,    2,    64,   320,    2,  1266>,
        block_fft_implementation<10,    2,   10,    8,    16,   320,    6,  1267>,
        block_fft_implementation<10,    2,   10,    8,    16,   160,   12,  1268>
    >;
};

template<> struct block_fft_record<84, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<42,    2,   42,    2,    32,   336,    2,  1270>,
        block_fft_implementation<42,    2,   42,    2,    32,   168,    4,  1269>
    >;
};

template<> struct block_fft_record<88, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<44,    2,   44,    2,    32,   176,    4,  1271>,
        block_fft_implementation<44,    2,   44,    2,    32,   352,    2,  1272>,
        block_fft_implementation<22,    2,   22,    4,    16,   352,    4,  1273>,
        block_fft_implementation<22,    2,   22,    4,    16,   176,    8,  1274>
    >;
};

template<> struct block_fft_record<92, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<46,    2,   46,    2,    32,   368,    2,  1276>,
        block_fft_implementation<46,    2,   46,    2,    32,   184,    4,  1275>
    >;
};

template<> struct block_fft_record<96, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<12,    2,   12,    8,    16,   384,    4,  1278>,
        block_fft_implementation<24,    4,   24,    4,    14,   384,    2,  1277>,
        block_fft_implementation<24,    4,   24,    4,    32,   192,    4,  1279>,
        block_fft_implementation< 6,    2,    6,   16,    16,   384,    8,  1280>,
        block_fft_implementation<12,    2,   12,    8,    16,   192,    8,  1281>,
        block_fft_implementation<48,    2,   48,    2,    30,   384,    2,  1282>,
        block_fft_implementation< 6,    2,    6,   16,    32,   192,   16,  1283>,
        block_fft_implementation<48,    2,   48,    2,    64,   192,    4,  1284>
    >;
};

template<> struct block_fft_record<104, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<52,    2,   52,    2,    32,   208,    4,  1285>,
        block_fft_implementation<52,    2,   52,    2,    28,   416,    2,  1286>,
        block_fft_implementation<26,    2,   26,    4,    32,   416,    4,  1287>,
        block_fft_implementation<26,    2,   26,    4,    16,   208,    8,  1288>
    >;
};

template<> struct block_fft_record<108, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<18,    6,   18,    6,    42,   432,    2,  1290>,
        block_fft_implementation<18,    6,   18,    6,    42,   216,    4,  1289>,
        block_fft_implementation< 6,    3,    6,   18,    14,   432,    4,  1295>,
        block_fft_implementation<36,    3,   36,    3,    42,   216,    4,  1291>,
        block_fft_implementation<54,    2,   54,    2,    32,   216,    4,  1292>,
        block_fft_implementation< 6,    3,    6,   18,    14,   216,    8,  1297>,
        block_fft_implementation<54,    2,   54,    2,    56,   432,    2,  1294>,
        block_fft_implementation<36,    3,   36,    3,   160,   432,    2,  1293>,
        block_fft_implementation<12,    3,   12,    9,    14,   432,    4,  1298>,
        block_fft_implementation<12,    3,   12,    9,    14,   216,    8,  1296>
    >;
};

template<> struct block_fft_record<112, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<28,    4,   28,    4,    16,   224,    4,  1299>,
        block_fft_implementation<28,    4,   28,    4,    16,   448,    2,  1300>,
        block_fft_implementation<56,    2,   56,    2,    32,   224,    4,  1301>,
        block_fft_implementation<56,    2,   56,    2,    54,   448,    2,  1302>,
        block_fft_implementation<14,    2,   14,    8,    16,   448,    6,  1303>,
        block_fft_implementation<14,    2,   14,    8,    16,   224,   12,  1304>
    >;
};

template<> struct block_fft_record<116, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<58,    2,   58,    2,    32,   232,    4,  1305>,
        block_fft_implementation<58,    2,   58,    2,   128,   464,    2,  1306>
    >;
};

template<> struct block_fft_record<120, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<60,    2,   60,    2,    30,   240,    4,  1307>,
        block_fft_implementation<30,    2,   30,    4,    16,   240,    8,  1310>,
        block_fft_implementation<30,    2,   30,    4,    32,   480,    4,  1309>,
        block_fft_implementation<60,    2,   60,    2,    24,   480,    2,  1308>
    >;
};

template<> struct block_fft_record<124, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<62,    2,   62,    2,    32,   248,    4,  1311>,
        block_fft_implementation<62,    2,   62,    2,   128,   496,    2,  1312>
    >;
};

template<> struct block_fft_record<136, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<34,    2,   34,    4,    16,   272,    8,  1313>,
        block_fft_implementation<34,    2,   34,    4,    28,   544,    4,  1314>
    >;
};

template<> struct block_fft_record<152, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<38,    2,   38,    4,    16,   304,    8,  1315>,
        block_fft_implementation<38,    2,   38,    4,    64,   608,    4,  1316>
    >;
};

template<> struct block_fft_record<160, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<20,    2,   20,    8,     8,   640,    4,  1318>,
        block_fft_implementation<40,    4,   40,    4,    32,   640,    2,  1317>,
        block_fft_implementation<40,    4,   40,    4,    16,   320,    4,  1319>,
        block_fft_implementation<10,    2,   10,   16,     8,   640,    8,  1320>,
        block_fft_implementation<20,    2,   20,    8,    16,   320,    8,  1321>,
        block_fft_implementation<10,    2,   10,   16,    16,   320,   16,  1322>
    >;
};

template<> struct block_fft_record<168, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<42,    2,   42,    4,    16,   672,    4,  1324>,
        block_fft_implementation<42,    2,   42,    4,    16,   336,    8,  1323>
    >;
};

template<> struct block_fft_record<176, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<44,    4,   44,    4,    16,   704,    2,  1326>,
        block_fft_implementation<44,    4,   44,    4,    16,   352,    4,  1325>,
        block_fft_implementation<22,    2,   22,    8,     8,   704,    6,  1327>,
        block_fft_implementation<22,    2,   22,    8,     8,   352,   12,  1328>
    >;
};

template<> struct block_fft_record<180, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<30,    6,   30,    6,    42,   720,    2,  1330>,
        block_fft_implementation<30,    6,   30,    6,    42,   360,    4,  1329>,
        block_fft_implementation<60,    3,   60,    3,    42,   360,    4,  1331>,
        block_fft_implementation<60,    3,   60,    3,    34,   720,    2,  1332>
    >;
};

template<> struct block_fft_record<184, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<46,    2,   46,    4,    16,   736,    4,  1334>,
        block_fft_implementation<46,    2,   46,    4,    16,   368,    8,  1333>
    >;
};

template<> struct block_fft_record<192, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<24,    8,   24,    8,     8,   384,    4,  1335>,
        block_fft_implementation<24,    8,   24,    8,    32,   768,    2,  1336>,
        block_fft_implementation<12,    4,   12,   16,     4,   768,    4,  1337>,
        block_fft_implementation<12,    4,   12,   16,     8,   384,    8,  1338>,
        block_fft_implementation<48,    4,   48,    4,    16,   384,    4,  1339>,
        block_fft_implementation< 6,    2,    6,   32,     8,   768,   10,  1341>,
        block_fft_implementation<48,    4,   48,    4,    14,   768,    2,  1340>,
        block_fft_implementation< 6,    2,    6,   32,    16,   384,   20,  1342>
    >;
};

template<> struct block_fft_record<200, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<20,   10,   20,   10,     6,   400,    4,  1343>,
        block_fft_implementation<20,   10,   20,   10,    50,   800,    2,  1344>,
        block_fft_implementation<40,    5,   40,    5,    12,   400,    4,  1345>,
        block_fft_implementation<40,    5,   40,    5,    50,   800,    2,  1347>,
        block_fft_implementation<10,    2,   10,   20,     6,   800,    4,  1346>,
        block_fft_implementation<10,    2,   10,   20,     6,   400,    8,  1349>,
        block_fft_implementation<50,    2,   50,    4,    16,   400,    8,  1348>,
        block_fft_implementation<50,    2,   50,    4,    16,   800,    4,  1350>
    >;
};

template<> struct block_fft_record<208, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<52,    4,   52,    4,    16,   416,    4,  1351>,
        block_fft_implementation<52,    4,   52,    4,    14,   832,    2,  1352>,
        block_fft_implementation<26,    2,   26,    8,     8,   832,    6,  1353>,
        block_fft_implementation<26,    2,   26,    8,     8,   416,   12,  1354>
    >;
};

template<> struct block_fft_record<224, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<28,    2,   28,    8,     8,   896,    4,  1355>,
        block_fft_implementation<56,    4,   56,    4,    16,   448,    4,  1356>,
        block_fft_implementation<56,    4,   56,    4,    26,   896,    2,  1357>,
        block_fft_implementation<14,    2,   14,   16,     8,   896,    8,  1358>,
        block_fft_implementation<28,    2,   28,    8,     8,   448,    8,  1359>,
        block_fft_implementation<14,    2,   14,   16,     8,   448,   16,  1360>
    >;
};

template<> struct block_fft_record<232, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<58,    2,   58,    4,    16,   464,    8,  1361>,
        block_fft_implementation<58,    2,   58,    4,    64,   928,    4,  1362>
    >;
};

template<> struct block_fft_record<240, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<60,    4,   60,    4,    16,   480,    4,  1363>,
        block_fft_implementation<60,    4,   60,    4,    14,   960,    2,  1364>,
        block_fft_implementation<30,    2,   30,    8,     8,   480,   12,  1365>,
        block_fft_implementation<30,    2,   30,    8,    16,   960,    6,  1366>
    >;
};

template<> struct block_fft_record<248, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<62,    2,   62,    4,    16,   496,    8,  1367>,
        block_fft_implementation<62,    2,   62,    4,    64,   992,    4,  1368>
    >;
};

template<> struct block_fft_record<252, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<42,    6,   42,    6,    42,  1008,    2,  1370>,
        block_fft_implementation<42,    6,   42,    6,    10,   504,    4,  1369>
    >;
};

template<> struct block_fft_record<272, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<34,    2,   34,    8,     8,  1088,    6,  1372>,
        block_fft_implementation<34,    2,   34,    8,     8,   544,   12,  1371>
    >;
};

template<> struct block_fft_record<288, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<24,   12,   24,   12,    10,   576,    4,  1373>,
        block_fft_implementation<24,   12,   24,   12,    10,  1152,    2,  1374>,
        block_fft_implementation<12,    2,   12,   24,    10,  1152,    4,  1376>,
        block_fft_implementation<12,    2,   12,   24,    10,   576,    8,  1375>,
        block_fft_implementation<48,    6,   48,    6,    10,   576,    4,  1378>,
        block_fft_implementation< 6,    2,    6,   48,     4,  1152,    8,  1379>,
        block_fft_implementation<36,    2,   36,    8,     8,  1152,    4,  1377>,
        block_fft_implementation<18,    2,   18,   16,     4,  1152,    8,  1380>,
        block_fft_implementation<36,    2,   36,    8,     8,   576,    8,  1382>,
        block_fft_implementation<48,    6,   48,    6,    10,  1152,    2,  1381>,
        block_fft_implementation< 6,    2,    6,   48,     4,   576,   16,  1383>,
        block_fft_implementation<18,    2,   18,   16,     8,   576,   16,  1384>
    >;
};

template<> struct block_fft_record<300, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<30,   10,   30,   10,     6,  1200,    2,  1386>,
        block_fft_implementation<30,   10,   30,   10,     6,   600,    4,  1385>,
        block_fft_implementation<60,    5,   60,    5,    12,   600,    4,  1387>,
        block_fft_implementation<60,    5,   60,    5,    50,  1200,    2,  1388>
    >;
};

template<> struct block_fft_record<304, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<38,    2,   38,    8,     8,   608,   12,  1389>,
        block_fft_implementation<38,    2,   38,    8,    16,  1216,    6,  1390>
    >;
};

template<> struct block_fft_record<320, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<20,    4,   20,   16,     4,  1280,    4,  1392>,
        block_fft_implementation<40,    8,   40,    8,     8,   640,    4,  1391>,
        block_fft_implementation<40,    8,   40,    8,    16,  1280,    2,  1393>,
        block_fft_implementation<20,    4,   20,   16,     4,   640,    8,  1394>,
        block_fft_implementation<10,    2,   10,   32,     4,  1280,   10,  1395>,
        block_fft_implementation<10,    2,   10,   32,     4,   640,   20,  1396>
    >;
};

template<> struct block_fft_record<336, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<42,    2,   42,    8,     8,  1344,    6,  1398>,
        block_fft_implementation<42,    2,   42,    8,     8,   672,   12,  1397>
    >;
};

template<> struct block_fft_record<352, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<44,    2,   44,    8,     8,  1408,    4,  1399>,
        block_fft_implementation<22,    2,   22,   16,     4,  1408,    8,  1400>,
        block_fft_implementation<44,    2,   44,    8,     8,   704,    8,  1401>,
        block_fft_implementation<22,    2,   22,   16,     4,   704,   16,  1402>
    >;
};

template<> struct block_fft_record<360, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<60,    6,   60,    6,    10,   720,    4,  1403>,
        block_fft_implementation<60,    6,   60,    6,    42,  1440,    2,  1404>,
        block_fft_implementation<30,    2,   30,   12,    10,  1440,    4,  1405>,
        block_fft_implementation<30,    2,   30,   12,    10,   720,    8,  1406>
    >;
};

template<> struct block_fft_record<368, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<46,    2,   46,    8,     8,  1472,    6,  1408>,
        block_fft_implementation<46,    2,   46,    8,     8,   736,   12,  1407>
    >;
};

template<> struct block_fft_record<384, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<48,    8,   48,    8,     8,   768,    4,  1409>,
        block_fft_implementation<24,    2,   24,   16,     4,   768,    8,  1410>,
        block_fft_implementation<12,    2,   12,   32,     2,  1536,    6,  1413>,
        block_fft_implementation<24,    2,   24,   16,    16,  1536,    4,  1411>,
        block_fft_implementation<12,    2,   12,   32,     4,   768,   12,  1412>,
        block_fft_implementation<48,    8,   48,    8,    16,  1536,    2,  1414>,
        block_fft_implementation< 6,    2,    6,   64,     4,  1536,   12,  1415>,
        block_fft_implementation< 6,    2,    6,   64,     8,   768,   24,  1416>
    >;
};

template<> struct block_fft_record<392, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<28,   14,   28,   14,    18,   784,    4,  1417>,
        block_fft_implementation<28,   14,   28,   14,    18,  1568,    2,  1420>,
        block_fft_implementation<56,    7,   56,    7,    18,   784,    4,  1418>,
        block_fft_implementation<14,    2,   14,   28,    18,  1568,    4,  1419>,
        block_fft_implementation<56,    7,   56,    7,    32,  1568,    2,  1422>,
        block_fft_implementation<14,    2,   14,   28,     2,   784,    8,  1421>
    >;
};

template<> struct block_fft_record<416, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<52,    2,   52,    8,     8,  1664,    4,  1424>,
        block_fft_implementation<26,    2,   26,   16,     4,  1664,    8,  1423>,
        block_fft_implementation<52,    2,   52,    8,     8,   832,    8,  1425>,
        block_fft_implementation<26,    2,   26,   16,     4,   832,   16,  1426>
    >;
};

template<> struct block_fft_record<432, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<36,   12,   36,   12,    10,   864,    4,  1427>,
        block_fft_implementation<36,   12,   36,   12,    42,  1728,    2,  1428>,
        block_fft_implementation<12,    3,   12,   36,    14,  1728,    4,  1430>,
        block_fft_implementation<12,    3,   12,   36,    14,   864,    8,  1429>,
        block_fft_implementation< 6,    2,    6,   72,    14,  1728,    6,  1432>,
        block_fft_implementation<24,    3,   24,   18,    14,   864,    8,  1431>,
        block_fft_implementation<24,    3,   24,   18,    14,  1728,    4,  1435>,
        block_fft_implementation<18,    2,   18,   24,    10,  1728,    6,  1433>,
        block_fft_implementation<48,    3,   48,    9,    14,   864,    8,  1436>,
        block_fft_implementation<54,    2,   54,    8,     8,   864,   12,  1438>,
        block_fft_implementation< 6,    2,    6,   72,    14,   864,   12,  1434>,
        block_fft_implementation<54,    2,   54,    8,    14,  1728,    6,  1439>,
        block_fft_implementation<18,    2,   18,   24,    10,   864,   12,  1437>,
        block_fft_implementation<48,    3,   48,    9,    14,  1728,    4,  1440>
    >;
};

template<> struct block_fft_record<448, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<56,    8,   56,    8,     8,   896,    4,  1441>,
        block_fft_implementation<28,    4,   28,   16,     4,  1792,    4,  1442>,
        block_fft_implementation<28,    4,   28,   16,     4,   896,    8,  1443>,
        block_fft_implementation<56,    8,   56,    8,    28,  1792,    2,  1444>,
        block_fft_implementation<14,    2,   14,   32,     2,  1792,   10,  1445>,
        block_fft_implementation<14,    2,   14,   32,     2,   896,   20,  1446>
    >;
};

template<> struct block_fft_record<464, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<58,    2,   58,    8,     8,   928,   12,  1447>,
        block_fft_implementation<58,    2,   58,    8,     8,  1856,    6,  1448>
    >;
};

template<> struct block_fft_record<480, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<30,    2,   30,   16,     8,  1920,    8,  1449>,
        block_fft_implementation<60,    2,   60,    8,     6,  1920,    4,  1450>,
        block_fft_implementation<60,    2,   60,    8,     8,   960,    8,  1451>,
        block_fft_implementation<30,    2,   30,   16,     4,   960,   16,  1452>
    >;
};

template<> struct block_fft_record<496, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<62,    2,   62,    8,     8,   992,   12,  1453>,
        block_fft_implementation<62,    2,   62,    8,     8,  1984,    6,  1454>
    >;
};

template<> struct block_fft_record<500, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<50,   10,   50,   10,    50,  2000,    2,  1456>,
        block_fft_implementation<50,   10,   50,   10,     6,  1000,    4,  1455>,
        block_fft_implementation<10,    5,   10,   50,    10,  2000,    4,  1457>,
        block_fft_implementation<20,    5,   20,   25,    10,  2000,    4,  1458>,
        block_fft_implementation<20,    5,   20,   25,    10,  1000,    8,  1460>,
        block_fft_implementation<10,    5,   10,   50,    10,  1000,    8,  1459>
    >;
};

template<> struct block_fft_record<504, half, fft_type::c2c, fft_direction::forward, 1200> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<42,    2,   42,   12,    10,  2016,    4,  1461>,
        block_fft_implementation<42,    2,   42,   12,    10,  1008,    8,  1462>
    >;
};

#ifdef CUFFTDX_ENABLE_RUNTIME_DATABASE
// Database function trait specialization for half precision, fft_direction::forward, architecture 1200
template<>
struct database_function<half, 1200, fft_direction::forward> {
    static constexpr auto get() {
        return CUFFTDX_STD::array{
make_database_record<33, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<34, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<35, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<37, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<38, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<39, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<40, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<41, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<42, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<43, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<44, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<45, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<46, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<47, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<48, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<50, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<51, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<52, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<53, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<54, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<55, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<56, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<57, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<58, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<59, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<60, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<61, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<62, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<63, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record< 2, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record< 4, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record< 8, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<16, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<32, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<64, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<128, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<256, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<512, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<1024, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<2048, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<4096, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<8192, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<16384, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record< 3, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record< 9, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<27, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<81, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<243, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<729, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<2187, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<6561, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<19683, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record< 5, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<25, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<125, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<625, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<3125, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<15625, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record< 7, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<49, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<343, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<2401, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<16807, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<11, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<121, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<1331, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record< 6, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<36, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<216, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<1296, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<7776, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<10, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<100, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<1000, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<10000, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<12, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<144, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<1728, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<13, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<169, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<2197, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<14, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<196, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<2744, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<15, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<225, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<3375, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<17, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<289, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<4913, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<18, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<324, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<5832, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<19, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<361, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<6859, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<20, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<400, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<8000, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<21, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<441, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<9261, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<22, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<484, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<10648, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<23, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<529, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<12167, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<24, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<576, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<13824, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<26, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<676, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<17576, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<28, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<784, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<21952, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<29, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<841, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<24389, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<30, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<900, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<31, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<961, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<68, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<72, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<76, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<80, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<84, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<88, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<92, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<96, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<104, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<108, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<112, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<116, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<120, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<124, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<136, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<152, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<160, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<168, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<176, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<180, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<184, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<192, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<200, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<208, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<224, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<232, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<240, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<248, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<252, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<272, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<288, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<300, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<304, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<320, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<336, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<352, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<360, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<368, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<384, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<392, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<416, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<432, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<448, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<464, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<480, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<496, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<500, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>(),
make_database_record<504, half, fft_type::c2c, fft_direction::forward,  1200, experimental::code_type::ptx,   14>()
};
    }
};
#endif // CUFFTDX_ENABLE_RUNTIME_DATABASE
