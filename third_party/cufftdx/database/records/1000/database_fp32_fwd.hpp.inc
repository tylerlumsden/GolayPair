//Copyright (c) 2019-2026, NVIDIA CORPORATION & AFFILIATES. All rights reserved.
//
//NVIDIA CORPORATION and its licensors retain all intellectual property
//and proprietary rights in and to this software, related documentation
//and any modifications thereto.  Any use, reproduction, disclosure or
//distribution of this software and related documentation without an express
//license agreement from NVIDIA CORPORATION is strictly prohibited.
//


template<> struct block_fft_record<33, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<33,   33,   33,    1,    32,     0,    0,     0>
    >;
};

template<> struct block_fft_record<34, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<34,   34,   34,    1,    32,     0,    0,     1>
    >;
};

template<> struct block_fft_record<35, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<35,   35,   35,    1,    32,     0,    0,     2>
    >;
};

template<> struct block_fft_record<37, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<37,   37,   37,    1,   256,     0,    0,     3>
    >;
};

template<> struct block_fft_record<38, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<38,   38,   38,    1,   256,     0,    0,     4>
    >;
};

template<> struct block_fft_record<39, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<39,   39,   39,    1,    32,     0,    0,     5>
    >;
};

template<> struct block_fft_record<40, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<20,    2,   20,    2,    32,   160,    4,     6>,
        block_fft_implementation<10,    2,   10,    4,    32,   320,    4,     7>,
        block_fft_implementation<10,    2,   10,    4,    16,   160,    8,     8>,
        block_fft_implementation<40,   40,   40,    1,    32,     0,    0,     9>
    >;
};

template<> struct block_fft_record<41, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<41,   41,   41,    1,    32,     0,    0,    10>
    >;
};

template<> struct block_fft_record<42, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<42,   42,   42,    1,   256,     0,    0,    11>
    >;
};

template<> struct block_fft_record<43, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<43,   43,   43,    1,    32,     0,    0,    12>
    >;
};

template<> struct block_fft_record<44, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<44,   44,   44,    1,   256,     0,    0,    13>
    >;
};

template<> struct block_fft_record<45, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<45,   45,   45,    1,    32,     0,    0,    14>
    >;
};

template<> struct block_fft_record<46, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<46,   46,   46,    1,    32,     0,    0,    15>
    >;
};

template<> struct block_fft_record<47, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<47,   47,   47,    1,    32,     0,    0,    16>
    >;
};

template<> struct block_fft_record<48, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<48,   48,   48,    1,    32,     0,    0,    17>
    >;
};

template<> struct block_fft_record<50, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<50,   50,   50,    1,   256,     0,    0,    18>
    >;
};

template<> struct block_fft_record<51, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<51,   51,   51,    1,    32,     0,    0,    19>
    >;
};

template<> struct block_fft_record<52, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<52,   52,   52,    1,    32,     0,    0,    20>
    >;
};

template<> struct block_fft_record<53, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<53,   53,   53,    1,   256,     0,    0,    21>
    >;
};

template<> struct block_fft_record<54, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<54,   54,   54,    1,    32,     0,    0,    22>
    >;
};

template<> struct block_fft_record<55, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<55,   55,   55,    1,    32,     0,    0,    23>
    >;
};

template<> struct block_fft_record<56, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<56,   56,   56,    1,    32,     0,    0,    24>
    >;
};

template<> struct block_fft_record<57, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<57,   57,   57,    1,    32,     0,    0,    25>
    >;
};

template<> struct block_fft_record<58, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<58,   58,   58,    1,    32,     0,    0,    26>
    >;
};

template<> struct block_fft_record<59, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<59,   59,   59,    1,   256,     0,    0,    27>
    >;
};

template<> struct block_fft_record<60, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<60,   60,   60,    1,   256,     0,    0,    28>
    >;
};

template<> struct block_fft_record<61, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<61,   61,   61,    1,   256,     0,    0,    29>
    >;
};

template<> struct block_fft_record<62, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<62,   62,   62,    1,    32,     0,    0,    30>
    >;
};

template<> struct block_fft_record<63, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<63,   63,   63,    1,    32,     0,    0,    31>
    >;
};

template<> struct block_fft_record<2, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 2,    2,    2,    1,   416,     0,    0,    32>
    >;
};

template<> struct block_fft_record<4, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 4,    4,    4,    1,   320,     0,    0,    33>,
        block_fft_implementation< 2,    2,    2,    2,   496,    16,    4,    35>,
        block_fft_implementation< 2,    2,    2,    2,   416,    32,    2,    34>
    >;
};

template<> struct block_fft_record<8, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 8,    8,    8,    1,   416,     0,    0,    36>,
        block_fft_implementation< 4,    2,    4,    2,   160,    32,    4,    37>,
        block_fft_implementation< 4,    2,    4,    2,   256,    64,    2,    38>,
        block_fft_implementation< 2,    2,    2,    4,   240,    32,    8,    40>,
        block_fft_implementation< 2,    2,    2,    4,   256,    64,    4,    39>
    >;
};

template<> struct block_fft_record<16, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<16,   16,   16,    1,   384,     0,    0,    41>,
        block_fft_implementation< 4,    4,    4,    4,    80,    64,    4,    42>,
        block_fft_implementation< 4,    4,    4,    4,    80,   128,    2,    43>,
        block_fft_implementation< 8,    2,    8,    2,   192,    64,    4,    44>,
        block_fft_implementation< 8,    2,    8,    2,   192,   128,    2,    45>,
        block_fft_implementation< 2,    2,    2,    8,   112,    64,   12,    47>,
        block_fft_implementation< 2,    2,    2,    8,   112,   128,    6,    46>
    >;
};

template<> struct block_fft_record<32, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<32,   32,   32,    1,   320,     0,    0,    48>,
        block_fft_implementation< 8,    4,    8,    4,    64,   256,    2,    49>,
        block_fft_implementation< 8,    4,    8,    4,    64,   128,    4,    50>,
        block_fft_implementation< 4,    2,    4,    8,    80,   256,    4,    51>,
        block_fft_implementation< 2,    2,    2,   16,    64,   256,    8,    53>,
        block_fft_implementation< 4,    2,    4,    8,    48,   128,    8,    52>,
        block_fft_implementation<16,    2,   16,    2,   128,   256,    2,    54>,
        block_fft_implementation< 2,    2,    2,   16,    64,   128,   16,    55>,
        block_fft_implementation<16,    2,   16,    2,    96,   128,    4,    56>
    >;
};

template<> struct block_fft_record<64, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 8,    8,    8,    8,    30,   512,    2,    58>,
        block_fft_implementation< 8,    8,    8,    8,    23,   256,    4,    57>,
        block_fft_implementation< 4,    4,    4,   16,    16,   512,    4,    59>,
        block_fft_implementation< 4,    4,    4,   16,    24,   256,    8,    60>,
        block_fft_implementation<16,    4,   16,    4,    28,   512,    2,    62>,
        block_fft_implementation<16,    4,   16,    4,    32,   256,    4,    61>,
        block_fft_implementation< 2,    2,    2,   32,    24,   512,   10,    64>,
        block_fft_implementation<32,    2,   32,    2,    64,   512,    2,    63>,
        block_fft_implementation< 2,    2,    2,   32,    23,   256,   20,    65>,
        block_fft_implementation<32,    2,   32,    2,    96,   256,    4,    66>,
        block_fft_implementation<64,   64,   64,    1,   256,     0,    0,    67>
    >;
};

template<> struct block_fft_record<128, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 8,    2,    8,   16,    16,  1024,    4,    69>,
        block_fft_implementation<16,    8,   16,    8,     8,   512,    4,    68>,
        block_fft_implementation<16,    8,   16,    8,    15,  1024,    2,    70>,
        block_fft_implementation< 8,    2,    8,   16,    12,   512,    8,    71>,
        block_fft_implementation< 4,    2,    4,   32,     8,  1024,    6,    72>,
        block_fft_implementation< 4,    2,    4,   32,    12,   512,   12,    73>,
        block_fft_implementation<32,    4,   32,    4,    30,  1024,    2,    74>,
        block_fft_implementation<32,    4,   32,    4,    31,   512,    4,    75>,
        block_fft_implementation< 2,    2,    2,   64,    10,  1024,   12,    76>,
        block_fft_implementation< 2,    2,    2,   64,    11,   512,   24,    77>
    >;
};

template<> struct block_fft_record<256, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<16,   16,   16,   16,     4,  1024,    4,    78>,
        block_fft_implementation< 8,    4,    8,   32,     6,  2048,    4,    80>,
        block_fft_implementation< 8,    4,    8,   32,     4,  1024,    8,    79>,
        block_fft_implementation<16,   16,   16,   16,     8,  2048,    2,    81>,
        block_fft_implementation<32,    8,   32,    8,    16,  2048,    2,    82>,
        block_fft_implementation< 4,    4,    4,   64,     4,  2048,    6,    83>,
        block_fft_implementation< 4,    4,    4,   64,     6,  1024,   12,    84>,
        block_fft_implementation<32,    8,   32,    8,    16,  1024,    4,    85>,
        block_fft_implementation< 2,    2,    2,  128,     3,  2048,   14,    86>,
        block_fft_implementation< 2,    2,    2,  128,     5,  1024,   28,    87>
    >;
};

template<> struct block_fft_record<512, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 8,    8,    8,   64,     2,  4096,    4,    90>,
        block_fft_implementation< 8,    8,    8,   64,     2,  2048,    8,    88>,
        block_fft_implementation<16,    2,   16,   32,     2,  2048,    8,    89>,
        block_fft_implementation<32,   16,   32,   16,     4,  4096,    2,    91>,
        block_fft_implementation<32,   16,   32,   16,     4,  2048,    4,    92>,
        block_fft_implementation<16,    2,   16,   32,     4,  4096,    4,    93>,
        block_fft_implementation< 4,    2,    4,  128,     2,  4096,    8,    94>,
        block_fft_implementation< 4,    2,    4,  128,     2,  2048,   16,    95>,
        block_fft_implementation< 2,    2,    2,  256,     1,  4096,   16,    96>,
        block_fft_implementation< 2,    2,    2,  256,     4,  2048,   32,    97>
    >;
};

template<> struct block_fft_record<1024, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<16,    4,   16,   64,     1,  4096,    8,    98>,
        block_fft_implementation<32,   32,   32,   32,     2,  8192,    2,   101>,
        block_fft_implementation<32,   32,   32,   32,     2,  4096,    4,    99>,
        block_fft_implementation< 8,    2,    8,  128,     2,  8192,    6,   100>,
        block_fft_implementation< 8,    2,    8,  128,     1,  4096,   12,   102>,
        block_fft_implementation<16,    4,   16,   64,     2,  8192,    4,   103>,
        block_fft_implementation< 4,    4,    4,  256,     1,  8192,    8,   104>,
        block_fft_implementation< 4,    4,    4,  256,     1,  4096,   16,   105>,
        block_fft_implementation< 2,    2,    2,  512,     1,  8192,   18,   106>,
        block_fft_implementation< 2,    2,    2,  512,     2,  4096,   36,   107>
    >;
};

template<> struct block_fft_record<2048, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<16,    8,   16,  128,     1,  8192,    8,   108>,
        block_fft_implementation< 8,    4,    8,  256,     1, 16384,    6,   109>,
        block_fft_implementation< 8,    4,    8,  256,     1,  8192,   12,   110>,
        block_fft_implementation<32,    2,   32,   64,     1, 16384,    4,   113>,
        block_fft_implementation<16,    8,   16,  128,     1, 16384,    4,   111>,
        block_fft_implementation<32,    2,   32,   64,     1,  8192,    8,   112>,
        block_fft_implementation< 4,    2,    4,  512,     1, 16384,   10,   114>,
        block_fft_implementation< 4,    2,    4,  512,     1,  8192,   20,   115>,
        block_fft_implementation< 2,    2,    2, 1024,     1, 16384,   20,   116>,
        block_fft_implementation< 2,    2,    2, 1024,     1,  8192,   40,   117>
    >;
};

template<> struct block_fft_record<4096, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<16,   16,   16,  256,     1, 16384,    8,   118>,
        block_fft_implementation< 8,    8,    8,  512,     1, 32768,    6,   120>,
        block_fft_implementation<32,    4,   32,  128,     1, 32768,    4,   123>,
        block_fft_implementation<16,   16,   16,  256,     1, 32768,    4,   121>,
        block_fft_implementation< 8,    8,    8,  512,     1, 16384,   12,   119>,
        block_fft_implementation<32,    4,   32,  128,     1, 16384,    8,   122>,
        block_fft_implementation< 4,    4,    4, 1024,     1, 32768,   10,   124>,
        block_fft_implementation< 4,    4,    4, 1024,     1, 16384,   20,   125>
    >;
};

template<> struct block_fft_record<8192, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<32,    8,   32,  256,     1, 65536,    4,   127>,
        block_fft_implementation<16,    2,   16,  512,     1, 32768,   12,   126>,
        block_fft_implementation< 8,    2,    8, 1024,     1, 65536,    8,   129>,
        block_fft_implementation<32,    8,   32,  256,     2, 32768,    8,   128>,
        block_fft_implementation<16,    2,   16,  512,     1, 65536,    6,   131>,
        block_fft_implementation< 8,    2,    8, 1024,     1, 32768,   16,   130>
    >;
};

template<> struct block_fft_record<16384, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<32,   16,   32,  512,     1, 131072,    4,  1463>,
        block_fft_implementation<16,    4,   16, 1024,     1, 65536,   12,   132>,
        block_fft_implementation<32,   16,   32,  512,     1, 65536,    8,   133>,
        block_fft_implementation<16,    4,   16, 1024,     1, 131072,    6,  1464>
    >;
};

template<> struct block_fft_record<32768, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<32,   32,   32, 1024,     1, 131072,    8,  1465>
    >;
};

template<> struct block_fft_record<3, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 3,    3,    3,    1,   512,     0,    0,   134>
    >;
};

template<> struct block_fft_record<9, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 9,    9,    9,    1,    32,     0,    0,   135>,
        block_fft_implementation< 3,    3,    3,    3,   336,    72,    2,   136>,
        block_fft_implementation< 3,    3,    3,    3,   128,    36,    4,   137>
    >;
};

template<> struct block_fft_record<27, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<27,   27,   27,    1,    32,     0,    0,   138>,
        block_fft_implementation< 9,    3,    9,    3,    21,   216,    2,   139>,
        block_fft_implementation< 9,    3,    9,    3,    21,   108,    4,   140>,
        block_fft_implementation< 3,    3,    3,    9,   112,   216,    4,   141>,
        block_fft_implementation< 3,    3,    3,    9,    64,   108,    8,   142>
    >;
};

template<> struct block_fft_record<81, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 9,    9,    9,    9,     7,   648,    2,   144>,
        block_fft_implementation< 9,    9,    9,    9,     7,   324,    4,   143>,
        block_fft_implementation<27,    3,   27,    3,    21,   324,    4,   145>,
        block_fft_implementation<27,    3,   27,    3,    21,   648,    2,   146>,
        block_fft_implementation< 3,    3,    3,   27,    23,   648,    6,   147>,
        block_fft_implementation< 3,    3,    3,   27,    27,   324,   12,   148>
    >;
};

template<> struct block_fft_record<243, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<27,    9,   27,    9,     7,  1944,    2,   150>,
        block_fft_implementation<27,    9,   27,    9,     7,   972,    4,   149>,
        block_fft_implementation< 9,    3,    9,   27,     7,  1944,    4,   151>,
        block_fft_implementation< 9,    3,    9,   27,     1,   972,    8,   152>,
        block_fft_implementation< 3,    3,    3,   81,     6,  1944,    8,   153>,
        block_fft_implementation< 3,    3,    3,   81,    11,   972,   16,   154>
    >;
};

template<> struct block_fft_record<729, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<27,   27,   27,   27,    14,  5832,    2,   155>,
        block_fft_implementation<27,   27,   27,   27,    14,  2916,    4,   156>,
        block_fft_implementation< 9,    9,    9,   81,     3,  5832,    4,   158>,
        block_fft_implementation< 9,    9,    9,   81,     3,  2916,    8,   157>,
        block_fft_implementation< 3,    3,    3,  243,     3,  5832,   10,   159>,
        block_fft_implementation< 3,    3,    3,  243,     3,  2916,   20,   160>
    >;
};

template<> struct block_fft_record<2187, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<27,    3,   27,   81,     3, 17496,    4,   161>,
        block_fft_implementation< 9,    3,    9,  243,     1, 17496,    6,   162>,
        block_fft_implementation<27,    3,   27,   81,     3,  8748,    8,   164>,
        block_fft_implementation< 9,    3,    9,  243,     2,  8748,   12,   163>,
        block_fft_implementation< 3,    3,    3,  729,     1, 17496,   12,   165>,
        block_fft_implementation< 3,    3,    3,  729,     1,  8748,   24,   166>
    >;
};

template<> struct block_fft_record<6561, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<27,    9,   27,  243,     2, 52488,    4,   167>,
        block_fft_implementation<27,    9,   27,  243,     3, 26244,    8,   168>,
        block_fft_implementation< 9,    9,    9,  729,     1, 52488,    6,   169>,
        block_fft_implementation< 9,    9,    9,  729,     1, 26244,   12,   170>
    >;
};

template<> struct block_fft_record<19683, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<27,   27,   27,  729,     1, 157464,    4,  1466>,
        block_fft_implementation<27,   27,   27,  729,     1, 78732,    8,  1467>
    >;
};

template<> struct block_fft_record<5, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 5,    5,    5,    1,    32,     0,    0,   171>
    >;
};

template<> struct block_fft_record<25, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<25,   25,   25,    1,   384,     0,    0,   172>,
        block_fft_implementation< 5,    5,    5,    5,    25,   200,    2,   173>,
        block_fft_implementation< 5,    5,    5,    5,    25,   100,    4,   174>
    >;
};

template<> struct block_fft_record<125, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<25,    5,   25,    5,     6,  1000,    2,   176>,
        block_fft_implementation<25,    5,   25,    5,     6,   500,    4,   175>,
        block_fft_implementation< 5,    5,    5,   25,     5,  1000,    4,   177>,
        block_fft_implementation< 5,    5,    5,   25,    15,   500,    8,   178>
    >;
};

template<> struct block_fft_record<625, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<25,   25,   25,   25,     5,  5000,    2,   180>,
        block_fft_implementation<25,   25,   25,   25,     5,  2500,    4,   179>,
        block_fft_implementation< 5,    5,    5,  125,     2,  5000,    6,   181>,
        block_fft_implementation< 5,    5,    5,  125,     1,  2500,   12,   182>
    >;
};

template<> struct block_fft_record<3125, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<25,    5,   25,  125,     1, 25000,    4,   184>,
        block_fft_implementation<25,    5,   25,  125,     1, 12500,    8,   183>,
        block_fft_implementation< 5,    5,    5,  625,     1, 25000,    8,   185>,
        block_fft_implementation< 5,    5,    5,  625,     1, 12500,   16,   186>
    >;
};

template<> struct block_fft_record<15625, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<25,   25,   25,  625,     1, 125000,    4,  1468>,
        block_fft_implementation<25,   25,   25,  625,     1, 62500,    8,   187>
    >;
};

template<> struct block_fft_record<7, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 7,    7,    7,    1,    32,     0,    0,   188>
    >;
};

template<> struct block_fft_record<49, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 7,    7,    7,    7,     9,   392,    2,   190>,
        block_fft_implementation< 7,    7,    7,    7,     9,   196,    4,   191>,
        block_fft_implementation<49,   49,   49,    1,   256,     0,    0,   189>
    >;
};

template<> struct block_fft_record<343, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 7,    7,    7,   49,     5,  2744,    4,   192>,
        block_fft_implementation< 7,    7,    7,   49,     5,  1372,    8,   193>
    >;
};

template<> struct block_fft_record<2401, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 7,    7,    7,  343,     2, 19208,    6,   194>,
        block_fft_implementation< 7,    7,    7,  343,     1,  9604,   12,   195>
    >;
};

template<> struct block_fft_record<16807, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<49,    7,   49,  343,     1, 134456,    4,  1469>,
        block_fft_implementation<49,    7,   49,  343,     1, 67228,    8,  1470>
    >;
};

template<> struct block_fft_record<11, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<11,   11,   11,    1,   288,     0,    0,   196>
    >;
};

template<> struct block_fft_record<121, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<11,   11,   11,   11,    11,   968,    2,   197>,
        block_fft_implementation<11,   11,   11,   11,    23,   484,    4,   198>
    >;
};

template<> struct block_fft_record<1331, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<11,   11,   11,  121,     1, 10648,    4,   199>,
        block_fft_implementation<11,   11,   11,  121,     1,  5324,    8,   200>
    >;
};

template<> struct block_fft_record<6, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 6,    6,    6,    1,    32,     0,    0,   201>
    >;
};

template<> struct block_fft_record<36, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 6,    6,    6,    6,    21,   288,    2,   202>,
        block_fft_implementation< 6,    6,    6,    6,    21,   144,    4,   203>,
        block_fft_implementation<36,   36,   36,    1,    32,     0,    0,   204>
    >;
};

template<> struct block_fft_record<216, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 6,    6,    6,   36,     7,  1728,    4,   205>,
        block_fft_implementation< 6,    6,    6,   36,     7,   864,    8,   206>
    >;
};

template<> struct block_fft_record<1296, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 6,    6,    6,  216,     2, 10368,    6,   207>,
        block_fft_implementation< 6,    6,    6,  216,     2,  5184,   12,   208>
    >;
};

template<> struct block_fft_record<7776, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<36,    6,   36,  216,     1, 62208,    4,   209>,
        block_fft_implementation<36,    6,   36,  216,     1, 31104,    8,   210>
    >;
};

template<> struct block_fft_record<10, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<10,   10,   10,    1,    32,     0,    0,   211>
    >;
};

template<> struct block_fft_record<100, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<10,   10,   10,   10,     3,   800,    2,   212>,
        block_fft_implementation<10,   10,   10,   10,     6,   400,    4,   213>
    >;
};

template<> struct block_fft_record<1000, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<10,   10,   10,  100,     3,  8000,    4,   214>,
        block_fft_implementation<10,   10,   10,  100,     3,  4000,    8,   215>
    >;
};

template<> struct block_fft_record<10000, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<10,   10,   10, 1000,     1, 80000,    6,  1471>,
        block_fft_implementation<10,   10,   10, 1000,     1, 40000,   12,   216>
    >;
};

template<> struct block_fft_record<12, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<12,   12,   12,    1,    64,     0,    0,   217>
    >;
};

template<> struct block_fft_record<144, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<12,   12,   12,   12,     5,  1152,    2,   219>,
        block_fft_implementation<12,   12,   12,   12,     5,   576,    4,   218>
    >;
};

template<> struct block_fft_record<1728, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<12,   12,   12,  144,     2, 13824,    4,   221>,
        block_fft_implementation<12,   12,   12,  144,     2,  6912,    8,   220>
    >;
};

template<> struct block_fft_record<13, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<13,   13,   13,    1,   256,     0,    0,   222>
    >;
};

template<> struct block_fft_record<169, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<13,   13,   13,   13,    19,  1352,    2,   223>,
        block_fft_implementation<13,   13,   13,   13,    19,   676,    4,   224>
    >;
};

template<> struct block_fft_record<2197, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<13,   13,   13,  169,     3, 17576,    4,   225>,
        block_fft_implementation<13,   13,   13,  169,     3,  8788,    8,   226>
    >;
};

template<> struct block_fft_record<14, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<14,   14,   14,    1,    32,     0,    0,   227>
    >;
};

template<> struct block_fft_record<196, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<14,   14,   14,   14,     9,  1568,    2,   229>,
        block_fft_implementation<14,   14,   14,   14,     2,   784,    4,   228>
    >;
};

template<> struct block_fft_record<2744, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<14,   14,   14,  196,     5, 21952,    4,   231>,
        block_fft_implementation<14,   14,   14,  196,     5, 10976,    8,   230>
    >;
};

template<> struct block_fft_record<15, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<15,   15,   15,    1,   384,     0,    0,   232>
    >;
};

template<> struct block_fft_record<225, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<15,   15,   15,   15,     2,  1800,    2,   233>,
        block_fft_implementation<15,   15,   15,   15,     2,   900,    4,   234>
    >;
};

template<> struct block_fft_record<3375, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<15,   15,   15,  225,     1, 27000,    4,   235>,
        block_fft_implementation<15,   15,   15,  225,     1, 13500,    8,   236>
    >;
};

template<> struct block_fft_record<17, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<17,   17,   17,    1,   256,     0,    0,   237>
    >;
};

template<> struct block_fft_record<289, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<17,   17,   17,   17,    15,  2312,    2,   238>,
        block_fft_implementation<17,   17,   17,   17,    15,  1156,    4,   239>
    >;
};

template<> struct block_fft_record<4913, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<17,   17,   17,  289,     2, 39304,    4,   240>,
        block_fft_implementation<17,   17,   17,  289,     3, 19652,    8,   241>
    >;
};

template<> struct block_fft_record<18, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<18,   18,   18,    1,   256,     0,    0,   242>
    >;
};

template<> struct block_fft_record<324, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<18,   18,   18,   18,     7,  2592,    2,   244>,
        block_fft_implementation<18,   18,   18,   18,     7,  1296,    4,   243>
    >;
};

template<> struct block_fft_record<5832, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<18,   18,   18,  324,     2, 46656,    4,   245>,
        block_fft_implementation<18,   18,   18,  324,     3, 23328,    8,   246>
    >;
};

template<> struct block_fft_record<19, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<19,   19,   19,    1,    32,     0,    0,   247>
    >;
};

template<> struct block_fft_record<361, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<19,   19,   19,   19,    20,  2888,    2,   248>,
        block_fft_implementation<19,   19,   19,   19,     3,  1444,    4,   249>
    >;
};

template<> struct block_fft_record<6859, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<19,   19,   19,  361,     1, 54872,    4,   250>,
        block_fft_implementation<19,   19,   19,  361,     1, 27436,    8,   251>
    >;
};

template<> struct block_fft_record<20, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<20,   20,   20,    1,    64,     0,    0,   252>
    >;
};

template<> struct block_fft_record<400, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<20,   20,   20,   20,     3,  3200,    2,   254>,
        block_fft_implementation<20,   20,   20,   20,     3,  1600,    4,   253>
    >;
};

template<> struct block_fft_record<8000, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<20,   20,   20,  400,     2, 64000,    4,   255>,
        block_fft_implementation<20,   20,   20,  400,     2, 32000,    8,   256>
    >;
};

template<> struct block_fft_record<21, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<21,   21,   21,    1,   512,     0,    0,   257>
    >;
};

template<> struct block_fft_record<441, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<21,   21,   21,   21,     3,  3528,    2,   258>,
        block_fft_implementation<21,   21,   21,   21,     3,  1764,    4,   259>
    >;
};

template<> struct block_fft_record<9261, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<21,   21,   21,  441,     1, 74088,    4,  1472>,
        block_fft_implementation<21,   21,   21,  441,     1, 37044,    8,   260>
    >;
};

template<> struct block_fft_record<22, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<22,   22,   22,    1,    32,     0,    0,   261>
    >;
};

template<> struct block_fft_record<484, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<22,   22,   22,   22,    29,  3872,    2,   263>,
        block_fft_implementation<22,   22,   22,   22,    11,  1936,    4,   262>
    >;
};

template<> struct block_fft_record<10648, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<22,   22,   22,  484,     1, 85184,    4,  1473>,
        block_fft_implementation<22,   22,   22,  484,     1, 42592,    8,   264>
    >;
};

template<> struct block_fft_record<23, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<23,   23,   23,    1,    32,     0,    0,   265>
    >;
};

template<> struct block_fft_record<529, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<23,   23,   23,   23,    22,  4232,    2,   266>,
        block_fft_implementation<23,   23,   23,   23,    22,  2116,    4,   267>
    >;
};

template<> struct block_fft_record<12167, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<23,   23,   23,  529,     1, 97336,    4,  1474>,
        block_fft_implementation<23,   23,   23,  529,     1, 48668,    8,   268>
    >;
};

template<> struct block_fft_record<24, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<24,   24,   24,    1,   256,     0,    0,   269>
    >;
};

template<> struct block_fft_record<576, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<24,   24,   24,   24,     5,  2304,    4,   270>,
        block_fft_implementation<24,   24,   24,   24,     4,  4608,    2,   271>
    >;
};

template<> struct block_fft_record<13824, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<24,   24,   24,  576,     1, 110592,    4,  1475>,
        block_fft_implementation<24,   24,   24,  576,     1, 55296,    8,   272>
    >;
};

template<> struct block_fft_record<26, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<26,   26,   26,    1,   320,     0,    0,   273>
    >;
};

template<> struct block_fft_record<676, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<26,   26,   26,   26,    24,  5408,    2,   275>,
        block_fft_implementation<26,   26,   26,   26,    24,  2704,    4,   274>
    >;
};

template<> struct block_fft_record<17576, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<26,   26,   26,  676,     1, 140608,    4,  1476>,
        block_fft_implementation<26,   26,   26,  676,     1, 70304,    8,  1477>
    >;
};

template<> struct block_fft_record<28, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<28,   28,   28,    1,   256,     0,    0,   276>
    >;
};

template<> struct block_fft_record<784, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<28,   28,   28,   28,     9,  6272,    2,   278>,
        block_fft_implementation<28,   28,   28,   28,     9,  3136,    4,   277>
    >;
};

template<> struct block_fft_record<21952, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<28,   28,   28,  784,     1, 175616,    4,  1528>,
        block_fft_implementation<28,   28,   28,  784,     1, 87808,    8,  1478>
    >;
};

template<> struct block_fft_record<29, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<29,   29,   29,    1,    32,     0,    0,   279>
    >;
};

template<> struct block_fft_record<841, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<29,   29,   29,   29,    13,  6728,    2,   280>,
        block_fft_implementation<29,   29,   29,   29,    13,  3364,    4,   281>
    >;
};

template<> struct block_fft_record<24389, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<29,   29,   29,  841,     1, 97556,    8,  1479>
    >;
};

template<> struct block_fft_record<30, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<30,   30,   30,    1,   320,     0,    0,   282>
    >;
};

template<> struct block_fft_record<900, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<30,   30,   30,   30,    17,  7200,    2,   284>,
        block_fft_implementation<30,   30,   30,   30,     2,  3600,    4,   283>
    >;
};

template<> struct block_fft_record<27000, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<30,   30,   30,  900,     1, 108000,    8,  1480>
    >;
};

template<> struct block_fft_record<31, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<31,   31,   31,    1,    32,     0,    0,   285>
    >;
};

template<> struct block_fft_record<961, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<31,   31,   31,   31,    12,  7688,    2,   286>,
        block_fft_implementation<31,   31,   31,   31,    16,  3844,    4,   287>
    >;
};

template<> struct block_fft_record<29791, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<31,   31,   31,  961,     1, 119164,    8,  1481>
    >;
};

template<> struct block_fft_record<68, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<34,    2,   34,    2,    16,   544,    2,   289>,
        block_fft_implementation<34,    2,   34,    2,    16,   272,    4,   288>
    >;
};

template<> struct block_fft_record<72, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<12,    6,   12,    6,    10,   576,    2,   291>,
        block_fft_implementation<12,    6,   12,    6,    21,   288,    4,   290>,
        block_fft_implementation<36,    2,   36,    2,    16,   288,    4,   292>,
        block_fft_implementation<24,    3,   24,    3,    21,   288,    4,   293>,
        block_fft_implementation<36,    2,   36,    2,    32,   576,    2,   294>,
        block_fft_implementation<24,    3,   24,    3,    20,   576,    2,   295>,
        block_fft_implementation< 6,    2,    6,   12,    21,   576,    4,   298>,
        block_fft_implementation<18,    2,   18,    4,    16,   576,    4,   296>,
        block_fft_implementation< 6,    2,    6,   12,    16,   288,    8,   299>,
        block_fft_implementation<18,    2,   18,    4,    16,   288,    8,   297>
    >;
};

template<> struct block_fft_record<76, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<38,    2,   38,    2,    16,   608,    2,   301>,
        block_fft_implementation<38,    2,   38,    2,    16,   304,    4,   300>
    >;
};

template<> struct block_fft_record<80, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<20,    4,   20,    4,    16,   320,    4,   302>,
        block_fft_implementation<20,    4,   20,    4,    16,   640,    2,   303>,
        block_fft_implementation<40,    2,   40,    2,    32,   320,    4,   304>,
        block_fft_implementation<40,    2,   40,    2,    30,   640,    2,   305>,
        block_fft_implementation<10,    2,   10,    8,    16,   640,    6,   306>,
        block_fft_implementation<10,    2,   10,    8,    16,   320,   12,   307>
    >;
};

template<> struct block_fft_record<84, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<42,    2,   42,    2,    16,   672,    2,   309>,
        block_fft_implementation<42,    2,   42,    2,    16,   336,    4,   308>
    >;
};

template<> struct block_fft_record<88, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<44,    2,   44,    2,    16,   352,    4,   310>,
        block_fft_implementation<44,    2,   44,    2,    16,   704,    2,   311>,
        block_fft_implementation<22,    2,   22,    4,     8,   704,    4,   313>,
        block_fft_implementation<22,    2,   22,    4,     8,   352,    8,   312>
    >;
};

template<> struct block_fft_record<92, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<46,    2,   46,    2,    16,   736,    2,   315>,
        block_fft_implementation<46,    2,   46,    2,    16,   368,    4,   314>
    >;
};

template<> struct block_fft_record<96, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<24,    4,   24,    4,    31,   768,    2,   316>,
        block_fft_implementation<12,    2,   12,    8,    16,   768,    4,   317>,
        block_fft_implementation<24,    4,   24,    4,    15,   384,    4,   318>,
        block_fft_implementation< 6,    2,    6,   16,     8,   768,    8,   320>,
        block_fft_implementation<12,    2,   12,    8,    16,   384,    8,   319>,
        block_fft_implementation<48,    2,   48,    2,    64,   768,    2,   321>,
        block_fft_implementation< 6,    2,    6,   16,    16,   384,   16,   322>,
        block_fft_implementation<48,    2,   48,    2,    31,   384,    4,   323>
    >;
};

template<> struct block_fft_record<104, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<52,    2,   52,    2,    16,   416,    4,   324>,
        block_fft_implementation<52,    2,   52,    2,    16,   832,    2,   325>,
        block_fft_implementation<26,    2,   26,    4,     8,   832,    4,   327>,
        block_fft_implementation<26,    2,   26,    4,     8,   416,    8,   326>
    >;
};

template<> struct block_fft_record<108, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<18,    6,   18,    6,     5,   864,    2,   329>,
        block_fft_implementation<54,    2,   54,    2,    16,   864,    2,   332>,
        block_fft_implementation<18,    6,   18,    6,    21,   432,    4,   328>,
        block_fft_implementation<36,    3,   36,    3,    21,   432,    4,   330>,
        block_fft_implementation<54,    2,   54,    2,    16,   432,    4,   331>,
        block_fft_implementation<36,    3,   36,    3,    21,   864,    2,   333>,
        block_fft_implementation< 6,    3,    6,   18,    14,   864,    4,   334>,
        block_fft_implementation< 6,    3,    6,   18,     7,   432,    8,   335>,
        block_fft_implementation<12,    3,   12,    9,     7,   432,    8,   336>,
        block_fft_implementation<12,    3,   12,    9,    10,   864,    4,   337>
    >;
};

template<> struct block_fft_record<112, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<28,    4,   28,    4,     8,   448,    4,   338>,
        block_fft_implementation<28,    4,   28,    4,    16,   896,    2,   339>,
        block_fft_implementation<56,    2,   56,    2,    32,   448,    4,   340>,
        block_fft_implementation<56,    2,   56,    2,    29,   896,    2,   341>,
        block_fft_implementation<14,    2,   14,    8,     8,   896,    6,   342>,
        block_fft_implementation<14,    2,   14,    8,     8,   448,   12,   343>
    >;
};

template<> struct block_fft_record<116, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<58,    2,   58,    2,    16,   928,    2,   345>,
        block_fft_implementation<58,    2,   58,    2,    16,   464,    4,   344>
    >;
};

template<> struct block_fft_record<120, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<60,    2,   60,    2,    16,   480,    4,   346>,
        block_fft_implementation<60,    2,   60,    2,    16,   960,    2,   349>,
        block_fft_implementation<30,    2,   30,    4,     8,   960,    4,   347>,
        block_fft_implementation<30,    2,   30,    4,     8,   480,    8,   348>
    >;
};

template<> struct block_fft_record<124, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<62,    2,   62,    2,    64,   992,    2,   351>,
        block_fft_implementation<62,    2,   62,    2,    64,   496,    4,   350>
    >;
};

template<> struct block_fft_record<136, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<34,    2,   34,    4,     8,  1088,    4,   353>,
        block_fft_implementation<34,    2,   34,    4,     8,   544,    8,   352>
    >;
};

template<> struct block_fft_record<152, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<38,    2,   38,    4,     8,  1216,    4,   355>,
        block_fft_implementation<38,    2,   38,    4,     8,   608,    8,   354>
    >;
};

template<> struct block_fft_record<160, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<40,    4,   40,    4,    16,  1280,    2,   358>,
        block_fft_implementation<20,    2,   20,    8,     8,  1280,    4,   356>,
        block_fft_implementation<40,    4,   40,    4,    14,   640,    4,   357>,
        block_fft_implementation<10,    2,   10,   16,     4,  1280,    8,   359>,
        block_fft_implementation<20,    2,   20,    8,     8,   640,    8,   360>,
        block_fft_implementation<10,    2,   10,   16,     8,   640,   16,   361>
    >;
};

template<> struct block_fft_record<168, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<42,    2,   42,    4,     8,  1344,    4,   363>,
        block_fft_implementation<42,    2,   42,    4,     8,   672,    8,   362>
    >;
};

template<> struct block_fft_record<176, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<44,    4,   44,    4,     8,   704,    4,   364>,
        block_fft_implementation<44,    4,   44,    4,     8,  1408,    2,   365>,
        block_fft_implementation<22,    2,   22,    8,     8,  1408,    6,   367>,
        block_fft_implementation<22,    2,   22,    8,     8,   704,   12,   366>
    >;
};

template<> struct block_fft_record<180, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<30,    6,   30,    6,     5,  1440,    2,   369>,
        block_fft_implementation<30,    6,   30,    6,    21,   720,    4,   368>,
        block_fft_implementation<60,    3,   60,    3,    21,  1440,    2,   371>,
        block_fft_implementation<60,    3,   60,    3,    21,   720,    4,   370>
    >;
};

template<> struct block_fft_record<184, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<46,    2,   46,    4,     8,  1472,    4,   373>,
        block_fft_implementation<46,    2,   46,    4,     8,   736,    8,   372>
    >;
};

template<> struct block_fft_record<192, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<24,    8,   24,    8,     8,  1536,    2,   375>,
        block_fft_implementation<24,    8,   24,    8,     8,   768,    4,   374>,
        block_fft_implementation<12,    4,   12,   16,     4,  1536,    4,   376>,
        block_fft_implementation<12,    4,   12,   16,     4,   768,    8,   377>,
        block_fft_implementation<48,    4,   48,    4,    30,  1536,    2,   379>,
        block_fft_implementation<48,    4,   48,    4,    16,   768,    4,   378>,
        block_fft_implementation< 6,    2,    6,   32,     4,  1536,   10,   380>,
        block_fft_implementation< 6,    2,    6,   32,     8,   768,   20,   381>
    >;
};

template<> struct block_fft_record<200, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<20,   10,   20,   10,     3,  1600,    2,   383>,
        block_fft_implementation<20,   10,   20,   10,     6,   800,    4,   382>,
        block_fft_implementation<40,    5,   40,    5,     6,   800,    4,   384>,
        block_fft_implementation<40,    5,   40,    5,    12,  1600,    2,   387>,
        block_fft_implementation<10,    2,   10,   20,     3,  1600,    4,   385>,
        block_fft_implementation<50,    2,   50,    4,     8,  1600,    4,   389>,
        block_fft_implementation<50,    2,   50,    4,     8,   800,    8,   386>,
        block_fft_implementation<10,    2,   10,   20,     3,   800,    8,   388>
    >;
};

template<> struct block_fft_record<208, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<52,    4,   52,    4,     8,   832,    4,   390>,
        block_fft_implementation<52,    4,   52,    4,     8,  1664,    2,   391>,
        block_fft_implementation<26,    2,   26,    8,     8,  1664,    6,   393>,
        block_fft_implementation<26,    2,   26,    8,     4,   832,   12,   392>
    >;
};

template<> struct block_fft_record<224, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<56,    4,   56,    4,    16,  1792,    2,   396>,
        block_fft_implementation<28,    2,   28,    8,     4,  1792,    4,   395>,
        block_fft_implementation<56,    4,   56,    4,    16,   896,    4,   394>,
        block_fft_implementation<14,    2,   14,   16,     4,  1792,    8,   397>,
        block_fft_implementation<28,    2,   28,    8,     8,   896,    8,   398>,
        block_fft_implementation<14,    2,   14,   16,     4,   896,   16,   399>
    >;
};

template<> struct block_fft_record<232, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<58,    2,   58,    4,    16,  1856,    4,   401>,
        block_fft_implementation<58,    2,   58,    4,     8,   928,    8,   400>
    >;
};

template<> struct block_fft_record<240, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<60,    4,   60,    4,     8,   960,    4,   402>,
        block_fft_implementation<60,    4,   60,    4,     8,  1920,    2,   403>,
        block_fft_implementation<30,    2,   30,    8,     8,  1920,    6,   404>,
        block_fft_implementation<30,    2,   30,    8,     4,   960,   12,   405>
    >;
};

template<> struct block_fft_record<248, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<62,    2,   62,    4,    16,  1984,    4,   407>,
        block_fft_implementation<62,    2,   62,    4,     8,   992,    8,   406>
    >;
};

template<> struct block_fft_record<252, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<42,    6,   42,    6,     5,  2016,    2,   409>,
        block_fft_implementation<42,    6,   42,    6,     5,  1008,    4,   408>
    >;
};

template<> struct block_fft_record<272, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<34,    2,   34,    8,     4,  2176,    6,   411>,
        block_fft_implementation<34,    2,   34,    8,     4,  1088,   12,   410>
    >;
};

template<> struct block_fft_record<288, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<24,   12,   24,   12,     5,  1152,    4,   412>,
        block_fft_implementation<24,   12,   24,   12,     5,  2304,    2,   413>,
        block_fft_implementation<12,    2,   12,   24,     4,  2304,    4,   415>,
        block_fft_implementation<12,    2,   12,   24,     5,  1152,    8,   414>,
        block_fft_implementation<36,    2,   36,    8,     4,  2304,    4,   416>,
        block_fft_implementation<48,    6,   48,    6,    10,  1152,    4,   417>,
        block_fft_implementation< 6,    2,    6,   48,     4,  2304,    8,   419>,
        block_fft_implementation<48,    6,   48,    6,    10,  2304,    2,   420>,
        block_fft_implementation<18,    2,   18,   16,     4,  2304,    8,   418>,
        block_fft_implementation<36,    2,   36,    8,     8,  1152,    8,   421>,
        block_fft_implementation< 6,    2,    6,   48,     4,  1152,   16,   422>,
        block_fft_implementation<18,    2,   18,   16,     4,  1152,   16,   423>
    >;
};

template<> struct block_fft_record<300, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<30,   10,   30,   10,     3,  2400,    2,   425>,
        block_fft_implementation<30,   10,   30,   10,     3,  1200,    4,   424>,
        block_fft_implementation<60,    5,   60,    5,    19,  2400,    2,   427>,
        block_fft_implementation<60,    5,   60,    5,     6,  1200,    4,   426>
    >;
};

template<> struct block_fft_record<304, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<38,    2,   38,    8,     4,  2432,    6,   429>,
        block_fft_implementation<38,    2,   38,    8,     4,  1216,   12,   428>
    >;
};

template<> struct block_fft_record<320, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<40,    8,   40,    8,     4,  2560,    2,   432>,
        block_fft_implementation<40,    8,   40,    8,     8,  1280,    4,   430>,
        block_fft_implementation<20,    4,   20,   16,     2,  2560,    4,   431>,
        block_fft_implementation<20,    4,   20,   16,     4,  1280,    8,   433>,
        block_fft_implementation<10,    2,   10,   32,     4,  2560,   10,   434>,
        block_fft_implementation<10,    2,   10,   32,     4,  1280,   20,   435>
    >;
};

template<> struct block_fft_record<336, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<42,    2,   42,    8,     4,  2688,    6,   437>,
        block_fft_implementation<42,    2,   42,    8,     4,  1344,   12,   436>
    >;
};

template<> struct block_fft_record<352, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<44,    2,   44,    8,     4,  2816,    4,   438>,
        block_fft_implementation<22,    2,   22,   16,     2,  2816,    8,   439>,
        block_fft_implementation<44,    2,   44,    8,     4,  1408,    8,   440>,
        block_fft_implementation<22,    2,   22,   16,     4,  1408,   16,   441>
    >;
};

template<> struct block_fft_record<360, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<60,    6,   60,    6,    16,  2880,    2,   445>,
        block_fft_implementation<60,    6,   60,    6,    21,  1440,    4,   442>,
        block_fft_implementation<30,    2,   30,   12,     5,  2880,    4,   444>,
        block_fft_implementation<30,    2,   30,   12,     5,  1440,    8,   443>
    >;
};

template<> struct block_fft_record<368, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<46,    2,   46,    8,     4,  2944,    6,   447>,
        block_fft_implementation<46,    2,   46,    8,     8,  1472,   12,   446>
    >;
};

template<> struct block_fft_record<384, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<24,    2,   24,   16,     4,  3072,    4,   450>,
        block_fft_implementation<48,    8,   48,    8,     8,  1536,    4,   448>,
        block_fft_implementation<24,    2,   24,   16,     4,  1536,    8,   449>,
        block_fft_implementation<12,    2,   12,   32,     2,  3072,    6,   452>,
        block_fft_implementation<12,    2,   12,   32,     2,  1536,   12,   451>,
        block_fft_implementation<48,    8,   48,    8,     8,  3072,    2,   453>,
        block_fft_implementation< 6,    2,    6,   64,     4,  3072,   12,   454>,
        block_fft_implementation< 6,    2,    6,   64,     4,  1536,   24,   455>
    >;
};

template<> struct block_fft_record<392, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<28,   14,   28,   14,     9,  3136,    2,   457>,
        block_fft_implementation<28,   14,   28,   14,     9,  1568,    4,   456>,
        block_fft_implementation<56,    7,   56,    7,    18,  1568,    4,   459>,
        block_fft_implementation<14,    2,   14,   28,     1,  3136,    4,   458>,
        block_fft_implementation<56,    7,   56,    7,    18,  3136,    2,   461>,
        block_fft_implementation<14,    2,   14,   28,     1,  1568,    8,   460>
    >;
};

template<> struct block_fft_record<416, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<52,    2,   52,    8,     8,  3328,    4,   462>,
        block_fft_implementation<26,    2,   26,   16,     2,  3328,    8,   463>,
        block_fft_implementation<52,    2,   52,    8,     4,  1664,    8,   464>,
        block_fft_implementation<26,    2,   26,   16,     4,  1664,   16,   465>
    >;
};

template<> struct block_fft_record<432, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<36,   12,   36,   12,     5,  3456,    2,   467>,
        block_fft_implementation<36,   12,   36,   12,     5,  1728,    4,   466>,
        block_fft_implementation<12,    3,   12,   36,     7,  3456,    4,   469>,
        block_fft_implementation<12,    3,   12,   36,     3,  1728,    8,   468>,
        block_fft_implementation< 6,    2,    6,   72,     3,  3456,    6,   471>,
        block_fft_implementation<24,    3,   24,   18,     7,  1728,    8,   470>,
        block_fft_implementation<18,    2,   18,   24,     4,  3456,    6,   473>,
        block_fft_implementation<24,    3,   24,   18,     7,  3456,    4,   472>,
        block_fft_implementation< 6,    2,    6,   72,     3,  1728,   12,   474>,
        block_fft_implementation<48,    3,   48,    9,     7,  1728,    8,   475>,
        block_fft_implementation<54,    2,   54,    8,     4,  3456,    6,   479>,
        block_fft_implementation<18,    2,   18,   24,     5,  1728,   12,   476>,
        block_fft_implementation<54,    2,   54,    8,     8,  1728,   12,   477>,
        block_fft_implementation<48,    3,   48,    9,     7,  3456,    4,   478>
    >;
};

template<> struct block_fft_record<448, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<56,    8,   56,    8,     4,  1792,    4,   480>,
        block_fft_implementation<28,    4,   28,   16,     2,  3584,    4,   481>,
        block_fft_implementation<56,    8,   56,    8,     4,  3584,    2,   482>,
        block_fft_implementation<28,    4,   28,   16,     2,  1792,    8,   483>,
        block_fft_implementation<14,    2,   14,   32,     2,  3584,   10,   484>,
        block_fft_implementation<14,    2,   14,   32,     2,  1792,   20,   485>
    >;
};

template<> struct block_fft_record<464, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<58,    2,   58,    8,    32,  3712,    6,   487>,
        block_fft_implementation<58,    2,   58,    8,    32,  1856,   12,   486>
    >;
};

template<> struct block_fft_record<480, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<30,    2,   30,   16,     2,  3840,    8,   488>,
        block_fft_implementation<60,    2,   60,    8,     4,  3840,    4,   490>,
        block_fft_implementation<60,    2,   60,    8,     8,  1920,    8,   489>,
        block_fft_implementation<30,    2,   30,   16,     2,  1920,   16,   491>
    >;
};

template<> struct block_fft_record<496, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<62,    2,   62,    8,     8,  1984,   12,   492>,
        block_fft_implementation<62,    2,   62,    8,     4,  3968,    6,   493>
    >;
};

template<> struct block_fft_record<500, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<50,   10,   50,   10,     3,  4000,    2,   495>,
        block_fft_implementation<50,   10,   50,   10,     3,  2000,    4,   494>,
        block_fft_implementation<10,    5,   10,   50,     5,  4000,    4,   497>,
        block_fft_implementation<20,    5,   20,   25,     5,  4000,    4,   498>,
        block_fft_implementation<20,    5,   20,   25,     5,  2000,    8,   496>,
        block_fft_implementation<10,    5,   10,   50,     5,  2000,    8,   499>
    >;
};

template<> struct block_fft_record<504, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<42,    2,   42,   12,     5,  4032,    4,   501>,
        block_fft_implementation<42,    2,   42,   12,     8,  2016,    8,   500>
    >;
};

template<> struct block_fft_record<20736, float, fft_type::c2c, fft_direction::forward, 1000> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<24,    3,   24,  864,     1, 165888,    6,  1486>,
        block_fft_implementation<36,    4,   36,  576,     1, 165888,    6,  1485>,
        block_fft_implementation<24,    3,   24,  864,     1, 82944,   12,  1482>,
        block_fft_implementation<36,    4,   36,  576,     1, 82944,   12,  1483>,
        block_fft_implementation<48,    3,   48,  432,     1, 82944,   12,  1484>,
        block_fft_implementation<48,    3,   48,  432,     1, 165888,    6,  1487>,
        block_fft_implementation<54,    2,   54,  384,     1, 165888,   14,  1488>,
        block_fft_implementation<54,    2,   54,  384,     1, 82944,   28,  1489>
    >;
};

#ifdef CUFFTDX_ENABLE_RUNTIME_DATABASE
// Database function trait specialization for float precision, fft_direction::forward, architecture 1000
template<>
struct database_function<float, 1000, fft_direction::forward> {
    static constexpr auto get() {
        return CUFFTDX_STD::array{
make_database_record<33, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<34, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<35, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<37, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<38, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<39, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<40, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<41, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<42, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<43, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<44, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<45, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<46, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<47, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<48, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<50, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<51, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<52, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<53, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<54, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<55, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<56, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<57, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<58, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<59, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<60, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<61, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<62, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<63, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record< 2, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record< 4, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record< 8, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<16, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<32, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<64, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<128, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<256, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<512, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<1024, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<2048, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<4096, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<8192, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<16384, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<32768, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record< 3, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record< 9, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<27, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<81, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<243, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<729, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<2187, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<6561, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<19683, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record< 5, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<25, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<125, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<625, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<3125, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<15625, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record< 7, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<49, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<343, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<2401, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<16807, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<11, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<121, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<1331, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record< 6, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<36, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<216, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<1296, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<7776, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<10, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<100, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<1000, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<10000, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<12, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<144, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<1728, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<13, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<169, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<2197, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<14, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<196, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<2744, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<15, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<225, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<3375, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<17, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<289, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<4913, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<18, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<324, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<5832, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<19, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<361, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<6859, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<20, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<400, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<8000, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<21, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<441, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<9261, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<22, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<484, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<10648, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<23, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<529, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<12167, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<24, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<576, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<13824, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<26, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<676, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<17576, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<28, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<784, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<21952, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<29, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<841, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<24389, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<30, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<900, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<27000, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<31, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<961, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<29791, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<68, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<72, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<76, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<80, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<84, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<88, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<92, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<96, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<104, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<108, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<112, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<116, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<120, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<124, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<136, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<152, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<160, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<168, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<176, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<180, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<184, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<192, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<200, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<208, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<224, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<232, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<240, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<248, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<252, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<272, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<288, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<300, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<304, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<320, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<336, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<352, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<360, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<368, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<384, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<392, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<416, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<432, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<448, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<464, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<480, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<496, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<500, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<504, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>(),
make_database_record<20736, float, fft_type::c2c, fft_direction::forward,  1000, experimental::code_type::ptx,   14>()
};
    }
};
#endif // CUFFTDX_ENABLE_RUNTIME_DATABASE
