//Copyright (c) 2019-2026, NVIDIA CORPORATION & AFFILIATES. All rights reserved.
//
//NVIDIA CORPORATION and its licensors retain all intellectual property
//and proprietary rights in and to this software, related documentation
//and any modifications thereto.  Any use, reproduction, disclosure or
//distribution of this software and related documentation without an express
//license agreement from NVIDIA CORPORATION is strictly prohibited.
//


template<> struct block_fft_record<33, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<33,   33,   33,    1,    32,     0,    0,   502>
    >;
};

template<> struct block_fft_record<34, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<34,   34,   34,    1,    32,     0,    0,   503>
    >;
};

template<> struct block_fft_record<35, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<35,   35,   35,    1,    32,     0,    0,   504>
    >;
};

template<> struct block_fft_record<37, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<37,   37,   37,    1,    32,     0,    0,   505>
    >;
};

template<> struct block_fft_record<38, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<38,   38,   38,    1,    32,     0,    0,   506>
    >;
};

template<> struct block_fft_record<39, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<39,   39,   39,    1,    32,     0,    0,   507>
    >;
};

template<> struct block_fft_record<40, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<20,    2,   20,    2,    32,   320,    4,   511>,
        block_fft_implementation<20,    2,   20,    2,    32,   640,    2,   510>,
        block_fft_implementation<10,    2,   10,    4,    16,   320,    8,   508>,
        block_fft_implementation<10,    2,   10,    4,    16,   640,    4,   509>,
        block_fft_implementation<40,   40,   40,    1,    32,     0,    0,   512>
    >;
};

template<> struct block_fft_record<2, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 2,    2,    2,    1,    32,     0,    0,   513>
    >;
};

template<> struct block_fft_record<4, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 4,    4,    4,    1,    96,     0,    0,   514>,
        block_fft_implementation< 2,    2,    2,    2,   128,    32,    4,   515>,
        block_fft_implementation< 2,    2,    2,    2,   128,    64,    2,   516>
    >;
};

template<> struct block_fft_record<8, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 8,    8,    8,    1,    32,     0,    0,   517>,
        block_fft_implementation< 4,    2,    4,    2,   128,    64,    4,   518>,
        block_fft_implementation< 2,    2,    2,    4,   128,    64,    8,   519>,
        block_fft_implementation< 4,    2,    4,    2,   128,   128,    2,   521>,
        block_fft_implementation< 2,    2,    2,    4,   112,   128,    4,   520>
    >;
};

template<> struct block_fft_record<16, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<16,   16,   16,    1,    32,     0,    0,   522>,
        block_fft_implementation< 4,    4,    4,    4,    64,   256,    2,   524>,
        block_fft_implementation< 4,    4,    4,    4,    64,   128,    4,   523>,
        block_fft_implementation< 2,    2,    2,    8,    48,   256,    6,   526>,
        block_fft_implementation< 8,    2,    8,    2,   128,   128,    4,   527>,
        block_fft_implementation< 8,    2,    8,    2,    64,   256,    2,   528>,
        block_fft_implementation< 2,    2,    2,    8,    64,   128,   12,   525>
    >;
};

template<> struct block_fft_record<32, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<32,   32,   32,    1,    32,     0,    0,   529>,
        block_fft_implementation< 8,    4,    8,    4,    64,   256,    4,   530>,
        block_fft_implementation< 4,    2,    4,    8,    24,   512,    4,   535>,
        block_fft_implementation< 8,    4,    8,    4,    48,   512,    2,   533>,
        block_fft_implementation< 4,    2,    4,    8,    27,   256,    8,   531>,
        block_fft_implementation<16,    2,   16,    2,    11,   512,    2,   537>,
        block_fft_implementation< 2,    2,    2,   16,    18,   512,    8,   534>,
        block_fft_implementation< 2,    2,    2,   16,    30,   256,   16,   532>,
        block_fft_implementation<16,    2,   16,    2,    64,   256,    4,   536>
    >;
};

template<> struct block_fft_record<64, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 8,    8,    8,    8,    16,   512,    4,   538>,
        block_fft_implementation< 4,    4,    4,   16,    20,   512,    8,   539>,
        block_fft_implementation< 4,    4,    4,   16,    12,  1024,    4,   540>,
        block_fft_implementation< 8,    8,    8,    8,    13,  1024,    2,   541>,
        block_fft_implementation<16,    4,   16,    4,     6,  1024,    2,   544>,
        block_fft_implementation<16,    4,   16,    4,    26,   512,    4,   542>,
        block_fft_implementation< 2,    2,    2,   32,     7,  1024,   10,   545>,
        block_fft_implementation< 2,    2,    2,   32,    12,   512,   20,   543>
    >;
};

template<> struct block_fft_record<128, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 8,    2,    8,   16,     8,  1024,    8,   552>,
        block_fft_implementation<16,    8,   16,    8,     4,  2048,    2,   547>,
        block_fft_implementation<16,    8,   16,    8,    16,  1024,    4,   546>,
        block_fft_implementation< 4,    2,    4,   32,     5,  2048,    6,   551>,
        block_fft_implementation< 4,    2,    4,   32,     8,  1024,   12,   548>,
        block_fft_implementation< 8,    2,    8,   16,     8,  2048,    4,   553>,
        block_fft_implementation< 2,    2,    2,   64,     6,  2048,   12,   550>,
        block_fft_implementation< 2,    2,    2,   64,     6,  1024,   24,   549>
    >;
};

template<> struct block_fft_record<256, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 8,    4,    8,   32,     4,  2048,    8,   558>,
        block_fft_implementation<16,   16,   16,   16,     2,  4096,    2,   557>,
        block_fft_implementation<16,   16,   16,   16,     2,  2048,    4,   555>,
        block_fft_implementation< 4,    4,    4,   64,     2,  4096,    6,   556>,
        block_fft_implementation< 4,    4,    4,   64,     4,  2048,   12,   554>,
        block_fft_implementation< 8,    4,    8,   32,     4,  4096,    4,   560>,
        block_fft_implementation< 2,    2,    2,  128,     3,  2048,   28,   559>,
        block_fft_implementation< 2,    2,    2,  128,     2,  4096,   14,   561>
    >;
};

template<> struct block_fft_record<512, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 8,    8,    8,   64,     2,  4096,    8,   562>,
        block_fft_implementation< 8,    8,    8,   64,     2,  8192,    4,   563>,
        block_fft_implementation<16,    2,   16,   32,     1,  8192,    4,   569>,
        block_fft_implementation<16,    2,   16,   32,     4,  4096,    8,   568>,
        block_fft_implementation< 4,    2,    4,  128,     2,  4096,   16,   564>,
        block_fft_implementation< 4,    2,    4,  128,     1,  8192,    8,   565>,
        block_fft_implementation< 2,    2,    2,  256,     2,  4096,   32,   566>,
        block_fft_implementation< 2,    2,    2,  256,     1,  8192,   16,   567>
    >;
};

template<> struct block_fft_record<1024, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 8,    2,    8,  128,     1,  8192,   12,   576>,
        block_fft_implementation<16,    4,   16,   64,     2,  8192,    8,   572>,
        block_fft_implementation< 4,    4,    4,  256,     1,  8192,   16,   570>,
        block_fft_implementation< 4,    4,    4,  256,     1, 16384,    8,   571>,
        block_fft_implementation<16,    4,   16,   64,     2, 16384,    4,   574>,
        block_fft_implementation< 8,    2,    8,  128,     1, 16384,    6,   577>,
        block_fft_implementation< 2,    2,    2,  512,     1, 16384,   18,   573>,
        block_fft_implementation< 2,    2,    2,  512,     1,  8192,   36,   575>
    >;
};

template<> struct block_fft_record<2048, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 8,    4,    8,  256,     1, 16384,   12,   580>,
        block_fft_implementation<16,    8,   16,  128,     1, 16384,    8,   578>,
        block_fft_implementation<16,    8,   16,  128,     1, 32768,    4,   581>,
        block_fft_implementation< 8,    4,    8,  256,     1, 32768,    6,   584>,
        block_fft_implementation< 4,    2,    4,  512,     1, 16384,   20,   579>,
        block_fft_implementation< 4,    2,    4,  512,     1, 32768,   10,   582>,
        block_fft_implementation< 2,    2,    2, 1024,     1, 16384,   40,   585>,
        block_fft_implementation< 2,    2,    2, 1024,     1, 32768,   20,   583>
    >;
};

template<> struct block_fft_record<4096, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 8,    8,    8,  512,     1, 32768,   12,   589>,
        block_fft_implementation<16,   16,   16,  256,     1, 32768,    8,   590>,
        block_fft_implementation<16,   16,   16,  256,     1, 65536,    4,   588>,
        block_fft_implementation< 8,    8,    8,  512,     1, 65536,    6,   591>,
        block_fft_implementation< 4,    4,    4, 1024,     1, 32768,   20,   586>,
        block_fft_implementation< 4,    4,    4, 1024,     1, 65536,   10,   587>
    >;
};

template<> struct block_fft_record<8192, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<16,    2,   16,  512,     1, 65536,   12,   593>,
        block_fft_implementation< 8,    2,    8, 1024,     1, 65536,   16,   592>
    >;
};

template<> struct block_fft_record<3, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 3,    3,    3,    1,    64,     0,    0,   594>
    >;
};

template<> struct block_fft_record<9, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 9,    9,    9,    1,    32,     0,    0,   595>,
        block_fft_implementation< 3,    3,    3,    3,    80,    72,    4,   596>,
        block_fft_implementation< 3,    3,    3,    3,    64,   144,    2,   597>
    >;
};

template<> struct block_fft_record<27, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<27,   27,   27,    1,   128,     0,    0,   598>,
        block_fft_implementation< 9,    3,    9,    3,    21,   216,    4,   601>,
        block_fft_implementation< 9,    3,    9,    3,    80,   432,    2,   602>,
        block_fft_implementation< 3,    3,    3,    9,    30,   216,    8,   599>,
        block_fft_implementation< 3,    3,    3,    9,    23,   432,    4,   600>
    >;
};

template<> struct block_fft_record<81, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 9,    9,    9,    9,    14,  1296,    2,   606>,
        block_fft_implementation< 9,    9,    9,    9,    14,   648,    4,   605>,
        block_fft_implementation<27,    3,   27,    3,    10,   648,    4,   607>,
        block_fft_implementation<27,    3,   27,    3,     9,  1296,    2,   608>,
        block_fft_implementation< 3,    3,    3,   27,     8,  1296,    6,   604>,
        block_fft_implementation< 3,    3,    3,   27,    13,   648,   12,   603>
    >;
};

template<> struct block_fft_record<243, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<27,    9,   27,    9,    14,  1944,    4,   611>,
        block_fft_implementation<27,    9,   27,    9,     3,  3888,    2,   612>,
        block_fft_implementation< 9,    3,    9,   27,     9,  3888,    4,   614>,
        block_fft_implementation< 9,    3,    9,   27,     9,  1944,    8,   613>,
        block_fft_implementation< 3,    3,    3,   81,     3,  3888,    8,   609>,
        block_fft_implementation< 3,    3,    3,   81,     3,  1944,   16,   610>
    >;
};

template<> struct block_fft_record<729, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 9,    9,    9,   81,     3, 11664,    4,   619>,
        block_fft_implementation< 9,    9,    9,   81,     3,  5832,    8,   618>,
        block_fft_implementation<27,   27,   27,   27,     1,  5832,    4,   617>,
        block_fft_implementation<27,   27,   27,   27,     1, 11664,    2,   620>,
        block_fft_implementation< 3,    3,    3,  243,     1,  5832,   20,   616>,
        block_fft_implementation< 3,    3,    3,  243,     1, 11664,   10,   615>
    >;
};

template<> struct block_fft_record<2187, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 9,    3,    9,  243,     1, 17496,   12,   623>,
        block_fft_implementation< 9,    3,    9,  243,     1, 34992,    6,   624>,
        block_fft_implementation< 3,    3,    3,  729,     1, 17496,   24,   622>,
        block_fft_implementation< 3,    3,    3,  729,     1, 34992,   12,   621>
    >;
};

template<> struct block_fft_record<6561, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 9,    9,    9,  729,     1, 52488,   12,   625>
    >;
};

template<> struct block_fft_record<5, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 5,    5,    5,    1,    64,     0,    0,   626>
    >;
};

template<> struct block_fft_record<25, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<25,   25,   25,    1,   128,     0,    0,   627>,
        block_fft_implementation< 5,    5,    5,    5,    25,   400,    2,   629>,
        block_fft_implementation< 5,    5,    5,    5,    25,   200,    4,   628>
    >;
};

template<> struct block_fft_record<125, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 5,    5,    5,   25,     5,  2000,    4,   632>,
        block_fft_implementation< 5,    5,    5,   25,     5,  1000,    8,   630>,
        block_fft_implementation<25,    5,   25,    5,    25,  1000,    4,   631>,
        block_fft_implementation<25,    5,   25,    5,     6,  2000,    2,   633>
    >;
};

template<> struct block_fft_record<625, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<25,   25,   25,   25,     5,  5000,    4,   634>,
        block_fft_implementation< 5,    5,    5,  125,     1,  5000,   12,   636>,
        block_fft_implementation< 5,    5,    5,  125,     1, 10000,    6,   637>,
        block_fft_implementation<25,   25,   25,   25,     5, 10000,    2,   635>
    >;
};

template<> struct block_fft_record<3125, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 5,    5,    5,  625,     1, 50000,    8,   639>,
        block_fft_implementation< 5,    5,    5,  625,     1, 25000,   16,   638>
    >;
};

template<> struct block_fft_record<7, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 7,    7,    7,    1,    32,     0,    0,   640>
    >;
};

template<> struct block_fft_record<49, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 7,    7,    7,    7,    18,   392,    4,   641>,
        block_fft_implementation< 7,    7,    7,    7,    18,   784,    2,   642>
    >;
};

template<> struct block_fft_record<343, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 7,    7,    7,   49,     5,  5488,    4,   644>,
        block_fft_implementation< 7,    7,    7,   49,     5,  2744,    8,   643>
    >;
};

template<> struct block_fft_record<2401, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 7,    7,    7,  343,     1, 38416,    6,   646>,
        block_fft_implementation< 7,    7,    7,  343,     1, 19208,   12,   645>
    >;
};

template<> struct block_fft_record<11, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<11,   11,   11,    1,    32,     0,    0,   647>
    >;
};

template<> struct block_fft_record<121, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<11,   11,   11,   11,    23,  1936,    2,   649>,
        block_fft_implementation<11,   11,   11,   11,    23,   968,    4,   648>
    >;
};

template<> struct block_fft_record<1331, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<11,   11,   11,  121,     1, 10648,    8,   650>,
        block_fft_implementation<11,   11,   11,  121,     1, 21296,    4,   651>
    >;
};

template<> struct block_fft_record<6, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 6,    6,    6,    1,    32,     0,    0,   652>
    >;
};

template<> struct block_fft_record<36, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 6,    6,    6,    6,    21,   576,    2,   654>,
        block_fft_implementation< 6,    6,    6,    6,    21,   288,    4,   653>,
        block_fft_implementation<36,   36,   36,    1,    32,     0,    0,   655>
    >;
};

template<> struct block_fft_record<216, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 6,    6,    6,   36,     7,  1728,    8,   656>,
        block_fft_implementation< 6,    6,    6,   36,     7,  3456,    4,   657>
    >;
};

template<> struct block_fft_record<1296, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation< 6,    6,    6,  216,     1, 10368,   12,   658>,
        block_fft_implementation< 6,    6,    6,  216,     1, 20736,    6,   659>
    >;
};

template<> struct block_fft_record<7776, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<36,    6,   36,  216,     1, 62208,    8,   660>
    >;
};

template<> struct block_fft_record<10, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<10,   10,   10,    1,    32,     0,    0,   661>
    >;
};

template<> struct block_fft_record<100, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<10,   10,   10,   10,     3,  1600,    2,   663>,
        block_fft_implementation<10,   10,   10,   10,     3,   800,    4,   662>
    >;
};

template<> struct block_fft_record<1000, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<10,   10,   10,  100,     5, 16000,    4,   665>,
        block_fft_implementation<10,   10,   10,  100,     1,  8000,    8,   664>
    >;
};

template<> struct block_fft_record<10000, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<10,   10,   10, 1000,     1, 80000,   12,  1497>
    >;
};

template<> struct block_fft_record<12, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<12,   12,   12,    1,    32,     0,    0,   666>
    >;
};

template<> struct block_fft_record<144, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<12,   12,   12,   12,    10,  1152,    4,   667>,
        block_fft_implementation<12,   12,   12,   12,     5,  2304,    2,   668>
    >;
};

template<> struct block_fft_record<1728, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<12,   12,   12,  144,     2, 13824,    8,   669>,
        block_fft_implementation<12,   12,   12,  144,     3, 27648,    4,   670>
    >;
};

template<> struct block_fft_record<13, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<13,   13,   13,    1,    32,     0,    0,   671>
    >;
};

template<> struct block_fft_record<169, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<13,   13,   13,   13,    19,  1352,    4,   672>,
        block_fft_implementation<13,   13,   13,   13,     9,  2704,    2,   673>
    >;
};

template<> struct block_fft_record<2197, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<13,   13,   13,  169,     3, 17576,    8,   674>,
        block_fft_implementation<13,   13,   13,  169,     2, 35152,    4,   675>
    >;
};

template<> struct block_fft_record<14, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<14,   14,   14,    1,    32,     0,    0,   676>
    >;
};

template<> struct block_fft_record<196, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<14,   14,   14,   14,     9,  1568,    4,   677>,
        block_fft_implementation<14,   14,   14,   14,     9,  3136,    2,   678>
    >;
};

template<> struct block_fft_record<2744, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<14,   14,   14,  196,     1, 43904,    4,   680>,
        block_fft_implementation<14,   14,   14,  196,     1, 21952,    8,   679>
    >;
};

template<> struct block_fft_record<15, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<15,   15,   15,    1,    32,     0,    0,   681>
    >;
};

template<> struct block_fft_record<225, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<15,   15,   15,   15,     2,  1800,    4,   682>,
        block_fft_implementation<15,   15,   15,   15,     8,  3600,    2,   683>
    >;
};

template<> struct block_fft_record<3375, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<15,   15,   15,  225,     1, 27000,    8,   684>,
        block_fft_implementation<15,   15,   15,  225,     1, 54000,    4,   685>
    >;
};

template<> struct block_fft_record<17, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<17,   17,   17,    1,    32,     0,    0,   686>
    >;
};

template<> struct block_fft_record<289, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<17,   17,   17,   17,     7,  2312,    4,   687>,
        block_fft_implementation<17,   17,   17,   17,     7,  4624,    2,   688>
    >;
};

template<> struct block_fft_record<4913, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<17,   17,   17,  289,     1, 39304,    8,   689>,
        block_fft_implementation<17,   17,   17,  289,     1, 78608,    4,  1498>
    >;
};

template<> struct block_fft_record<18, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<18,   18,   18,    1,    32,     0,    0,   690>
    >;
};

template<> struct block_fft_record<324, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<18,   18,   18,   18,     7,  2592,    4,   691>,
        block_fft_implementation<18,   18,   18,   18,     7,  5184,    2,   692>
    >;
};

template<> struct block_fft_record<5832, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<18,   18,   18,  324,     1, 46656,    8,   693>,
        block_fft_implementation<18,   18,   18,  324,     1, 93312,    4,  1499>
    >;
};

template<> struct block_fft_record<19, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<19,   19,   19,    1,    32,     0,    0,   694>
    >;
};

template<> struct block_fft_record<361, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<19,   19,   19,   19,    20,  2888,    4,   695>,
        block_fft_implementation<19,   19,   19,   19,    13,  5776,    2,   696>
    >;
};

template<> struct block_fft_record<6859, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<19,   19,   19,  361,     1, 54872,    8,   697>
    >;
};

template<> struct block_fft_record<20, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<20,   20,   20,    1,    32,     0,    0,   698>
    >;
};

template<> struct block_fft_record<400, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<20,   20,   20,   20,     6,  3200,    4,   699>,
        block_fft_implementation<20,   20,   20,   20,     6,  6400,    2,   700>
    >;
};

template<> struct block_fft_record<8000, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<20,   20,   20,  400,     1, 64000,    8,   701>
    >;
};

template<> struct block_fft_record<21, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<21,   21,   21,    1,    32,     0,    0,   702>
    >;
};

template<> struct block_fft_record<441, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<21,   21,   21,   21,     6,  3528,    4,   703>,
        block_fft_implementation<21,   21,   21,   21,     6,  7056,    2,   704>
    >;
};

template<> struct block_fft_record<9261, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<21,   21,   21,  441,     1, 74088,    8,  1503>
    >;
};

template<> struct block_fft_record<22, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<22,   22,   22,    1,    32,     0,    0,   705>
    >;
};

template<> struct block_fft_record<484, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<22,   22,   22,   22,     5,  3872,    4,   706>,
        block_fft_implementation<22,   22,   22,   22,     5,  7744,    2,   707>
    >;
};

template<> struct block_fft_record<10648, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<22,   22,   22,  484,     1, 85184,    8,  1504>
    >;
};

template<> struct block_fft_record<23, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<23,   23,   23,    1,    32,     0,    0,   708>
    >;
};

template<> struct block_fft_record<529, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<23,   23,   23,   23,    11,  8464,    2,   710>,
        block_fft_implementation<23,   23,   23,   23,    11,  4232,    4,   709>
    >;
};

template<> struct block_fft_record<12167, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<23,   23,   23,  529,     1, 97336,    8,  1505>
    >;
};

template<> struct block_fft_record<24, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<24,   24,   24,    1,    32,     0,    0,   711>
    >;
};

template<> struct block_fft_record<576, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<24,   24,   24,   24,     5,  4608,    4,   712>,
        block_fft_implementation<24,   24,   24,   24,     1,  9216,    2,   713>
    >;
};

template<> struct block_fft_record<26, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<26,   26,   26,    1,    32,     0,    0,   714>
    >;
};

template<> struct block_fft_record<676, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<26,   26,   26,   26,     9,  5408,    4,   715>,
        block_fft_implementation<26,   26,   26,   26,     9, 10816,    2,   716>
    >;
};

template<> struct block_fft_record<28, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<28,   28,   28,    1,    32,     0,    0,   717>
    >;
};

template<> struct block_fft_record<784, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<28,   28,   28,   28,     1,  6272,    4,   718>,
        block_fft_implementation<28,   28,   28,   28,     1, 12544,    2,   719>
    >;
};

template<> struct block_fft_record<29, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<29,   29,   29,    1,    32,     0,    0,   720>
    >;
};

template<> struct block_fft_record<841, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<29,   29,   29,   29,     4,  6728,    4,   721>,
        block_fft_implementation<29,   29,   29,   29,     4, 13456,    2,   722>
    >;
};

template<> struct block_fft_record<30, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<30,   30,   30,    1,    32,     0,    0,   723>
    >;
};

template<> struct block_fft_record<900, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<30,   30,   30,   30,     1,  7200,    4,   724>,
        block_fft_implementation<30,   30,   30,   30,     4, 14400,    2,   725>
    >;
};

template<> struct block_fft_record<31, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<31,   31,   31,    1,    32,     0,    0,   726>
    >;
};

template<> struct block_fft_record<961, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<31,   31,   31,   31,     4,  7688,    4,   727>,
        block_fft_implementation<31,   31,   31,   31,     4, 15376,    2,   728>
    >;
};

template<> struct block_fft_record<44, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<22,    2,   22,    2,    16,   352,    4,   729>,
        block_fft_implementation<22,    2,   22,    2,    16,   704,    2,   730>
    >;
};

template<> struct block_fft_record<48, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<12,    4,   12,    4,    32,   384,    4,   731>,
        block_fft_implementation<12,    4,   12,    4,     8,   768,    2,   732>,
        block_fft_implementation< 6,    2,    6,    8,     8,   768,    6,   734>,
        block_fft_implementation<24,    2,   24,    2,    64,   384,    4,   735>,
        block_fft_implementation<24,    2,   24,    2,    16,   768,    2,   736>,
        block_fft_implementation< 6,    2,    6,    8,    32,   384,   12,   733>
    >;
};

template<> struct block_fft_record<52, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<26,    2,   26,    2,    16,   416,    4,   737>,
        block_fft_implementation<26,    2,   26,    2,    14,   832,    2,   738>
    >;
};

template<> struct block_fft_record<56, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<28,    2,   28,    2,    16,   448,    4,   740>,
        block_fft_implementation<14,    2,   14,    4,     8,   448,    8,   739>,
        block_fft_implementation<14,    2,   14,    4,     8,   896,    4,   741>,
        block_fft_implementation<28,    2,   28,    2,    13,   896,    2,   742>
    >;
};

template<> struct block_fft_record<60, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<30,    2,   30,    2,    16,   480,    4,   743>,
        block_fft_implementation<30,    2,   30,    2,    12,   960,    2,   744>
    >;
};

template<> struct block_fft_record<68, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<34,    2,   34,    2,    64,   544,    4,   745>,
        block_fft_implementation<34,    2,   34,    2,    12,  1088,    2,   746>
    >;
};

template<> struct block_fft_record<72, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<12,    6,   12,    6,    21,   576,    4,   747>,
        block_fft_implementation<12,    6,   12,    6,     5,  1152,    2,   749>,
        block_fft_implementation<24,    3,   24,    3,    10,   576,    4,   748>,
        block_fft_implementation<36,    2,   36,    2,    16,   576,    4,   751>,
        block_fft_implementation<18,    2,   18,    4,     8,   576,    8,   750>,
        block_fft_implementation< 6,    2,    6,   12,    10,   576,    8,   752>,
        block_fft_implementation< 6,    2,    6,   12,    10,  1152,    4,   755>,
        block_fft_implementation<18,    2,   18,    4,     8,  1152,    4,   753>,
        block_fft_implementation<24,    3,   24,    3,    10,  1152,    2,   756>,
        block_fft_implementation<36,    2,   36,    2,    16,  1152,    2,   754>
    >;
};

template<> struct block_fft_record<76, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<38,    2,   38,    2,    16,   608,    4,   757>,
        block_fft_implementation<38,    2,   38,    2,    16,  1216,    2,   758>
    >;
};

template<> struct block_fft_record<80, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<20,    4,   20,    4,     8,   640,    4,   759>,
        block_fft_implementation<20,    4,   20,    4,     8,  1280,    2,   760>,
        block_fft_implementation<10,    2,   10,    8,     4,  1280,    6,   762>,
        block_fft_implementation<40,    2,   40,    2,    16,   640,    4,   763>,
        block_fft_implementation<10,    2,   10,    8,    16,   640,   12,   761>,
        block_fft_implementation<40,    2,   40,    2,    16,  1280,    2,   764>
    >;
};

template<> struct block_fft_record<84, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<42,    2,   42,    2,    64,   672,    4,   765>,
        block_fft_implementation<42,    2,   42,    2,    32,  1344,    2,   766>
    >;
};

template<> struct block_fft_record<88, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<22,    2,   22,    4,     8,   704,    8,   767>,
        block_fft_implementation<44,    2,   44,    2,    64,   704,    4,   768>,
        block_fft_implementation<22,    2,   22,    4,     8,  1408,    4,   769>,
        block_fft_implementation<44,    2,   44,    2,    32,  1408,    2,   770>
    >;
};

template<> struct block_fft_record<92, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<46,    2,   46,    2,    64,   736,    4,   771>,
        block_fft_implementation<46,    2,   46,    2,    48,  1472,    2,   772>
    >;
};

template<> struct block_fft_record<96, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<24,    4,   24,    4,     8,   768,    4,   773>,
        block_fft_implementation<12,    2,   12,    8,    16,   768,    8,   775>,
        block_fft_implementation<12,    2,   12,    8,     4,  1536,    4,   778>,
        block_fft_implementation<24,    4,   24,    4,     8,  1536,    2,   777>,
        block_fft_implementation< 6,    2,    6,   16,     8,   768,   16,   774>,
        block_fft_implementation< 6,    2,    6,   16,     4,  1536,    8,   776>,
        block_fft_implementation<48,    2,   48,    2,    16,   768,    4,   779>,
        block_fft_implementation<48,    2,   48,    2,    32,  1536,    2,   780>
    >;
};

template<> struct block_fft_record<104, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<26,    2,   26,    4,     8,   832,    8,   781>,
        block_fft_implementation<52,    2,   52,    2,    16,   832,    4,   782>,
        block_fft_implementation<26,    2,   26,    4,     7,  1664,    4,   783>,
        block_fft_implementation<52,    2,   52,    2,    32,  1664,    2,   784>
    >;
};

template<> struct block_fft_record<108, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<18,    6,   18,    6,    21,   864,    4,   785>,
        block_fft_implementation<18,    6,   18,    6,     5,  1728,    2,   788>,
        block_fft_implementation< 6,    3,    6,   18,     7,   864,    8,   789>,
        block_fft_implementation<36,    3,   36,    3,    10,   864,    4,   787>,
        block_fft_implementation< 6,    3,    6,   18,     7,  1728,    4,   792>,
        block_fft_implementation<54,    2,   54,    2,    16,   864,    4,   791>,
        block_fft_implementation<12,    3,   12,    9,     3,   864,    8,   786>,
        block_fft_implementation<12,    3,   12,    9,     3,  1728,    4,   790>,
        block_fft_implementation<36,    3,   36,    3,    24,  1728,    2,   793>,
        block_fft_implementation<54,    2,   54,    2,    32,  1728,    2,   794>
    >;
};

template<> struct block_fft_record<112, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<28,    4,   28,    4,     8,   896,    4,   795>,
        block_fft_implementation<14,    2,   14,    8,     4,  1792,    6,   799>,
        block_fft_implementation<28,    4,   28,    4,     6,  1792,    2,   796>,
        block_fft_implementation<14,    2,   14,    8,    16,   896,   12,   797>,
        block_fft_implementation<56,    2,   56,    2,    48,   896,    4,   798>,
        block_fft_implementation<56,    2,   56,    2,    32,  1792,    2,   800>
    >;
};

template<> struct block_fft_record<116, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<58,    2,   58,    2,    64,   928,    4,   801>,
        block_fft_implementation<58,    2,   58,    2,    32,  1856,    2,   802>
    >;
};

template<> struct block_fft_record<120, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<30,    2,   30,    4,     8,   960,    8,   803>,
        block_fft_implementation<60,    2,   60,    2,    48,   960,    4,   804>,
        block_fft_implementation<30,    2,   30,    4,     8,  1920,    4,   805>,
        block_fft_implementation<60,    2,   60,    2,    32,  1920,    2,   806>
    >;
};

template<> struct block_fft_record<124, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<62,    2,   62,    2,    64,   992,    4,   807>,
        block_fft_implementation<62,    2,   62,    2,    32,  1984,    2,   808>
    >;
};

template<> struct block_fft_record<136, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<34,    2,   34,    4,     8,  1088,    8,   809>,
        block_fft_implementation<34,    2,   34,    4,     6,  2176,    4,   810>
    >;
};

template<> struct block_fft_record<152, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<38,    2,   38,    4,    32,  1216,    8,   811>,
        block_fft_implementation<38,    2,   38,    4,    20,  2432,    4,   812>
    >;
};

template<> struct block_fft_record<160, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<20,    2,   20,    8,     4,  1280,    8,   816>,
        block_fft_implementation<40,    4,   40,    4,     8,  1280,    4,   813>,
        block_fft_implementation<20,    2,   20,    8,     4,  2560,    4,   818>,
        block_fft_implementation<10,    2,   10,   16,     2,  2560,    8,   817>,
        block_fft_implementation<10,    2,   10,   16,     2,  1280,   16,   814>,
        block_fft_implementation<40,    4,   40,    4,    18,  2560,    2,   815>
    >;
};

template<> struct block_fft_record<168, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<42,    2,   42,    4,     8,  1344,    8,   819>,
        block_fft_implementation<42,    2,   42,    4,    16,  2688,    4,   820>
    >;
};

template<> struct block_fft_record<176, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<44,    4,   44,    4,    31,  1408,    4,   821>,
        block_fft_implementation<22,    2,   22,    8,     4,  2816,    6,   824>,
        block_fft_implementation<22,    2,   22,    8,     4,  1408,   12,   823>,
        block_fft_implementation<44,    4,   44,    4,    24,  2816,    2,   822>
    >;
};

template<> struct block_fft_record<180, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<30,    6,   30,    6,     5,  1440,    4,   825>,
        block_fft_implementation<30,    6,   30,    6,     4,  2880,    2,   827>,
        block_fft_implementation<60,    3,   60,    3,    32,  1440,    4,   826>,
        block_fft_implementation<60,    3,   60,    3,    32,  2880,    2,   828>
    >;
};

template<> struct block_fft_record<184, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<46,    2,   46,    4,    32,  1472,    8,   829>,
        block_fft_implementation<46,    2,   46,    4,    24,  2944,    4,   830>
    >;
};

template<> struct block_fft_record<192, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<12,    4,   12,   16,     2,  1536,    8,   832>,
        block_fft_implementation<24,    8,   24,    8,     4,  1536,    4,   831>,
        block_fft_implementation<12,    4,   12,   16,     2,  3072,    4,   833>,
        block_fft_implementation<24,    8,   24,    8,     4,  3072,    2,   835>,
        block_fft_implementation<48,    4,   48,    4,     8,  1536,    4,   836>,
        block_fft_implementation< 6,    2,    6,   32,     4,  1536,   20,   834>,
        block_fft_implementation< 6,    2,    6,   32,     2,  3072,   10,   838>,
        block_fft_implementation<48,    4,   48,    4,    24,  3072,    2,   837>
    >;
};

template<> struct block_fft_record<200, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<20,   10,   20,   10,     3,  1600,    4,   839>,
        block_fft_implementation<20,   10,   20,   10,     3,  3200,    2,   841>,
        block_fft_implementation<10,    2,   10,   20,     6,  1600,    8,   844>,
        block_fft_implementation<40,    5,   40,    5,     6,  1600,    4,   840>,
        block_fft_implementation<10,    2,   10,   20,     6,  3200,    4,   846>,
        block_fft_implementation<50,    2,   50,    4,    30,  1600,    8,   842>,
        block_fft_implementation<40,    5,   40,    5,    24,  3200,    2,   845>,
        block_fft_implementation<50,    2,   50,    4,    16,  3200,    4,   843>
    >;
};

template<> struct block_fft_record<208, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<52,    4,   52,    4,    29,  1664,    4,   847>,
        block_fft_implementation<26,    2,   26,    8,     4,  3328,    6,   850>,
        block_fft_implementation<26,    2,   26,    8,     4,  1664,   12,   849>,
        block_fft_implementation<52,    4,   52,    4,    16,  3328,    2,   848>
    >;
};

template<> struct block_fft_record<224, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<28,    2,   28,    8,     4,  1792,    8,   853>,
        block_fft_implementation<14,    2,   14,   16,     2,  1792,   16,   852>,
        block_fft_implementation<56,    4,   56,    4,    27,  1792,    4,   851>,
        block_fft_implementation<14,    2,   14,   16,     2,  3584,    8,   854>,
        block_fft_implementation<28,    2,   28,    8,     3,  3584,    4,   855>,
        block_fft_implementation<56,    4,   56,    4,    16,  3584,    2,   856>
    >;
};

template<> struct block_fft_record<232, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<58,    2,   58,    4,    26,  1856,    8,   857>,
        block_fft_implementation<58,    2,   58,    4,    16,  3712,    4,   858>
    >;
};

template<> struct block_fft_record<240, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<60,    4,   60,    4,    25,  1920,    4,   859>,
        block_fft_implementation<30,    2,   30,    8,     4,  1920,   12,   860>,
        block_fft_implementation<30,    2,   30,    8,     4,  3840,    6,   862>,
        block_fft_implementation<60,    4,   60,    4,    16,  3840,    2,   861>
    >;
};

template<> struct block_fft_record<248, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<62,    2,   62,    4,    32,  1984,    8,   863>,
        block_fft_implementation<62,    2,   62,    4,    16,  3968,    4,   864>
    >;
};

template<> struct block_fft_record<252, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<42,    6,   42,    6,    21,  2016,    4,   865>,
        block_fft_implementation<42,    6,   42,    6,    16,  4032,    2,   866>
    >;
};

template<> struct block_fft_record<272, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<34,    2,   34,    8,     4,  2176,   12,   867>,
        block_fft_implementation<34,    2,   34,    8,    11,  4352,    6,   868>
    >;
};

template<> struct block_fft_record<288, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<24,   12,   24,   12,    10,  2304,    4,   869>,
        block_fft_implementation<12,    2,   12,   24,     5,  2304,    8,   878>,
        block_fft_implementation<36,    2,   36,    8,     4,  2304,    8,   870>,
        block_fft_implementation<12,    2,   12,   24,     5,  4608,    4,   880>,
        block_fft_implementation<18,    2,   18,   16,     2,  2304,   16,   871>,
        block_fft_implementation< 6,    2,    6,   48,     2,  2304,   16,   872>,
        block_fft_implementation<18,    2,   18,   16,     2,  4608,    8,   873>,
        block_fft_implementation<24,   12,   24,   12,     2,  4608,    2,   876>,
        block_fft_implementation<48,    6,   48,    6,     5,  2304,    4,   874>,
        block_fft_implementation< 6,    2,    6,   48,     2,  4608,    8,   877>,
        block_fft_implementation<36,    2,   36,    8,     3,  4608,    4,   875>,
        block_fft_implementation<48,    6,   48,    6,    16,  4608,    2,   879>
    >;
};

template<> struct block_fft_record<300, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<30,   10,   30,   10,     3,  2400,    4,   881>,
        block_fft_implementation<60,    5,   60,    5,    20,  2400,    4,   882>,
        block_fft_implementation<30,   10,   30,   10,    10,  4800,    2,   883>,
        block_fft_implementation<60,    5,   60,    5,    16,  4800,    2,   884>
    >;
};

template<> struct block_fft_record<304, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<38,    2,   38,    8,     4,  2432,   12,   885>,
        block_fft_implementation<38,    2,   38,    8,     4,  4864,    6,   886>
    >;
};

template<> struct block_fft_record<320, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<20,    4,   20,   16,     2,  2560,    8,   888>,
        block_fft_implementation<40,    8,   40,    8,     4,  2560,    4,   887>,
        block_fft_implementation<20,    4,   20,   16,     2,  5120,    4,   890>,
        block_fft_implementation<10,    2,   10,   32,     1,  5120,   10,   892>,
        block_fft_implementation<10,    2,   10,   32,     4,  2560,   20,   891>,
        block_fft_implementation<40,    8,   40,    8,     3,  5120,    2,   889>
    >;
};

template<> struct block_fft_record<336, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<42,    2,   42,    8,    16,  2688,   12,   893>,
        block_fft_implementation<42,    2,   42,    8,     4,  5376,    6,   894>
    >;
};

template<> struct block_fft_record<352, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<44,    2,   44,    8,     4,  2816,    8,   895>,
        block_fft_implementation<22,    2,   22,   16,     2,  5632,    8,   897>,
        block_fft_implementation<22,    2,   22,   16,     2,  2816,   16,   896>,
        block_fft_implementation<44,    2,   44,    8,     8,  5632,    4,   898>
    >;
};

template<> struct block_fft_record<360, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<30,    2,   30,   12,    10,  2880,    8,   900>,
        block_fft_implementation<60,    6,   60,    6,    17,  2880,    4,   899>,
        block_fft_implementation<30,    2,   30,   12,     2,  5760,    4,   901>,
        block_fft_implementation<60,    6,   60,    6,    16,  5760,    2,   902>
    >;
};

template<> struct block_fft_record<368, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<46,    2,   46,    8,    16,  2944,   12,   903>,
        block_fft_implementation<46,    2,   46,    8,     8,  5888,    6,   904>
    >;
};

template<> struct block_fft_record<384, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<12,    2,   12,   32,     1,  3072,   12,   908>,
        block_fft_implementation<24,    2,   24,   16,     2,  3072,    8,   911>,
        block_fft_implementation<12,    2,   12,   32,     1,  6144,    6,   910>,
        block_fft_implementation<48,    8,   48,    8,     4,  3072,    4,   905>,
        block_fft_implementation<24,    2,   24,   16,     2,  6144,    4,   912>,
        block_fft_implementation< 6,    2,    6,   64,     2,  3072,   24,   907>,
        block_fft_implementation< 6,    2,    6,   64,     1,  6144,   12,   909>,
        block_fft_implementation<48,    8,   48,    8,     8,  6144,    2,   906>
    >;
};

template<> struct block_fft_record<392, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<28,   14,   28,   14,     9,  3136,    4,   913>,
        block_fft_implementation<14,    2,   14,   28,     1,  3136,    8,   916>,
        block_fft_implementation<14,    2,   14,   28,     1,  6272,    4,   917>,
        block_fft_implementation<28,   14,   28,   14,     2,  6272,    2,   915>,
        block_fft_implementation<56,    7,   56,    7,    15,  3136,    4,   914>,
        block_fft_implementation<56,    7,   56,    7,     8,  6272,    2,   918>
    >;
};

template<> struct block_fft_record<416, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<52,    2,   52,    8,    14,  3328,    8,   920>,
        block_fft_implementation<26,    2,   26,   16,     2,  3328,   16,   919>,
        block_fft_implementation<26,    2,   26,   16,     2,  6656,    8,   921>,
        block_fft_implementation<52,    2,   52,    8,     8,  6656,    4,   922>
    >;
};

template<> struct block_fft_record<432, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<36,   12,   36,   12,    10,  3456,    4,   923>,
        block_fft_implementation<12,    3,   12,   36,     3,  3456,    8,   926>,
        block_fft_implementation< 6,    2,    6,   72,     3,  3456,   12,   929>,
        block_fft_implementation<24,    3,   24,   18,     7,  3456,    8,   927>,
        block_fft_implementation<12,    3,   12,   36,     3,  6912,    4,   930>,
        block_fft_implementation<18,    2,   18,   24,     5,  3456,   12,   928>,
        block_fft_implementation<18,    2,   18,   24,     5,  6912,    6,   932>,
        block_fft_implementation< 6,    2,    6,   72,     3,  6912,    6,   933>,
        block_fft_implementation<24,    3,   24,   18,     7,  6912,    4,   935>,
        block_fft_implementation<36,   12,   36,   12,     2,  6912,    2,   924>,
        block_fft_implementation<54,    2,   54,    8,    14,  3456,   12,   925>,
        block_fft_implementation<48,    3,   48,    9,     7,  3456,    8,   931>,
        block_fft_implementation<54,    2,   54,    8,     8,  6912,    6,   936>,
        block_fft_implementation<48,    3,   48,    9,     8,  6912,    4,   934>
    >;
};

template<> struct block_fft_record<448, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<28,    4,   28,   16,     2,  3584,    8,   938>,
        block_fft_implementation<56,    8,   56,    8,    13,  3584,    4,   937>,
        block_fft_implementation<28,    4,   28,   16,     2,  7168,    4,   940>,
        block_fft_implementation<14,    2,   14,   32,     1,  7168,   10,   942>,
        block_fft_implementation<14,    2,   14,   32,     1,  3584,   20,   941>,
        block_fft_implementation<56,    8,   56,    8,     8,  7168,    2,   939>
    >;
};

template<> struct block_fft_record<464, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<58,    2,   58,    8,    13,  3712,   12,   943>,
        block_fft_implementation<58,    2,   58,    8,     8,  7424,    6,   944>
    >;
};

template<> struct block_fft_record<480, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<30,    2,   30,   16,     8,  3840,   16,   945>,
        block_fft_implementation<60,    2,   60,    8,    12,  3840,    8,   946>,
        block_fft_implementation<30,    2,   30,   16,     2,  7680,    8,   947>,
        block_fft_implementation<60,    2,   60,    8,     8,  7680,    4,   948>
    >;
};

template<> struct block_fft_record<496, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<62,    2,   62,    8,    12,  3968,   12,   949>,
        block_fft_implementation<62,    2,   62,    8,     8,  7936,    6,   950>
    >;
};

template<> struct block_fft_record<500, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<10,    5,   10,   50,     5,  4000,    8,   953>,
        block_fft_implementation<50,   10,   50,   10,    12,  4000,    4,   951>,
        block_fft_implementation<20,    5,   20,   25,     5,  4000,    8,   952>,
        block_fft_implementation<10,    5,   10,   50,     2,  8000,    4,   954>,
        block_fft_implementation<20,    5,   20,   25,     5,  8000,    4,   956>,
        block_fft_implementation<50,   10,   50,   10,     8,  8000,    2,   955>
    >;
};

template<> struct block_fft_record<504, double, fft_type::c2c, fft_direction::forward, 860> {
    static constexpr bool defined = true;
    using blobs = type_list<
        block_fft_implementation<42,    2,   42,   12,    10,  4032,    8,   957>,
        block_fft_implementation<42,    2,   42,   12,     8,  8064,    4,   958>
    >;
};

#ifdef CUFFTDX_ENABLE_RUNTIME_DATABASE
// Database function trait specialization for double precision, fft_direction::forward, architecture 860
template<>
struct database_function<double, 860, fft_direction::forward> {
    static constexpr auto get() {
        return CUFFTDX_STD::array{
make_database_record<33, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<34, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<35, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<37, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<38, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<39, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<40, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record< 2, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record< 4, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record< 8, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<16, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<32, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<64, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<128, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<256, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<512, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<1024, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<2048, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<4096, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<8192, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record< 3, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record< 9, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<27, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<81, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<243, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<729, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<2187, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<6561, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record< 5, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<25, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<125, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<625, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<3125, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record< 7, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<49, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<343, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<2401, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<11, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<121, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<1331, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record< 6, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<36, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<216, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<1296, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<7776, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<10, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<100, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<1000, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<10000, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<12, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<144, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<1728, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<13, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<169, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<2197, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<14, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<196, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<2744, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<15, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<225, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<3375, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<17, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<289, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<4913, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<18, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<324, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<5832, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<19, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<361, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<6859, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<20, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<400, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<8000, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<21, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<441, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<9261, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<22, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<484, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<10648, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<23, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<529, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<12167, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<24, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<576, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<26, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<676, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<28, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<784, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<29, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<841, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<30, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<900, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<31, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<961, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<44, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<48, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<52, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<56, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<60, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<68, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<72, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<76, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<80, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<84, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<88, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<92, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<96, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<104, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<108, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<112, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<116, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<120, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<124, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<136, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<152, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<160, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<168, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<176, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<180, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<184, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<192, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<200, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<208, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<224, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<232, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<240, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<248, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<252, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<272, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<288, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<300, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<304, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<320, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<336, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<352, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<360, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<368, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<384, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<392, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<416, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<432, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<448, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<464, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<480, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<496, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<500, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>(),
make_database_record<504, double, fft_type::c2c, fft_direction::forward,   860, experimental::code_type::ptx,   14>()
};
    }
};
#endif // CUFFTDX_ENABLE_RUNTIME_DATABASE
