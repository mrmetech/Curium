// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017 The Curium developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of

    (     0, uint256("20438ea808f386bca78de64fc78320312af41d0d828763a9f5dd444d8ba7b54c"))
    (  1000, uint256("a8b2ab1d3f60ec9a54dee1b10164cabb9f6d8180389959c1f5f37fa9e012e3e8"))
    ( 10000, uint256("868c1e05ea03784fc00b43c30c1af4908397714c36add59c3380d0e7707a9782"))
    ( 40000	, uint256("02c0cedd92a31f4e3f73b8423d6b1d366c9650f20cc42910a8b5eea35a901d95"))
    (50000, uint256("8086a82a281deb7919d76efb31f1d9bfe9829a2ec4f4ca7350ac22ef3817990c"))
    (60000, uint256("15abab501e13158510aeea79011f1767000f366d31fa225635203e6af877106c"))
    (70000, uint256("f94cc246cd089eceed108f08333f4fc0150516635657c083defe1517b89bef03"))
    (81603, uint256("f0577a749d725d7e7f43a7203a7ece7013e96c9deaba94db45a510c2c22368ef"))
    (94255, uint256("ff6e698a7df1e927c0f348b05e8287e835220d74889f0a1afb6456d27d322ceb"))
    (200000, uint256("1ec54eee748fb62803c628f413066cb897d05a552ee28d028f20d7d7a69f76ae"))
    (300000, uint256("69356534f0a36d9ad72600a831936062fb7827a7df8d2bbca7046e9b822a3e84"))
    (400000, uint256("3852c6edec09e719dcbf6c78dd72af756f699bed7a71f755b030a9c08c7875ba"))
    (500000, uint256("890ce8dc028fcfd01d7c673589e2560dccdec3f052f5eab9efebffbafe9d86cb"))
    (600000, uint256("f62f6fbb0b1b901871de080a05cb6f64858028102ae58a20398421174db77f13"))
    (700000, uint256("87e7c895c50017f145b4fe50d3f31333523cad0389f8d3fb52958ef977ac7bcb"))
    (784600, uint256("aa9674333efbf557f3f15f852adde3880731dfb326ff73fe30df919d698e5d22"))
    (791800, uint256("041973e61963048218f91c72fad5eacd6056c455bcef6d633f607f6edc6c3989"))
    (849300, uint256("b5bc1303a62aacdd96aabc86342e9c4e1ce8c11548de6b2b15c1ec01fdfd6ec9"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,

 
    1574292097, // * UNIX timestamp of last checkpoint block

    1637633,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    1440        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x2b1a0f66712aad59ad283662d5b919415a25921ce89511d73019107e380485bf"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1504595227,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x2b1a0f66712aad59ad283662d5b919415a25921ce89511d73019107e380485bf"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1504595227,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus;
    bnTrustedModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

libzerocoin::ZerocoinParams* CChainParams::OldZerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus;
    bnTrustedModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xab;
        pchMessageStart[1] = 0xd8;
        pchMessageStart[2] = 0xe2;
        pchMessageStart[3] = 0xd5;
        vAlertPubKey = ParseHex("04659d53bd8f7ad9d34a17281febedac754e5a6eb136142d3a9c6c0ea21b6ed7498ceb3d872eed00ae755f7aeadaeb1d9ab5e1a8f1e7efcd0ddcb39d4623c12790");
        nDefaultPort = 18745;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Curium: 1 day
        nTargetSpacing = 1 * 60;  // Curium: 1 minute
        nMaturity = 50;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 1000000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;

        nModifierUpdateBlock = 468744;

        nZerocoinStartHeight = 11495;


        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "Curium May 15 2018 we began our quest for the new network";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1526939990;
        genesis.nBits = 0x207fffff;;
        genesis.nNonce = 0;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x20438ea808f386bca78de64fc78320312af41d0d828763a9f5dd444d8ba7b54c"));
        assert(genesis.hashMerkleRoot == uint256("0x8738140c726a5ee4eabd99024115280f825c57bae6decc2b14251b917152df4f"));

        vSeeds.push_back(CDNSSeedData("dns0", "dns0.curium.phore.io"));     // Primary DNS Seeder
        vSeeds.push_back(CDNSSeedData("dns1", "dns1.curium.phore.io"));    // Secondary DNS Seeder

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 60);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x01)(0xbc).convert_to_container<std::vector<unsigned char> >();

        bech32_hrp = "gp";

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04ba3e15d1276b37932e3861f920dedaa38e56ab9e1f05f789af06e763759652785bf96cc7375015abaaab6a58f18f20d022a3ccf7c0966f8781affee51dbc08f7";
        strObfuscationPoolDummyAddress = "RCYiHgGJJ6xGHqivmdZrYjRnhaYf6AJ2Mp";

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";



        nZerocoinLastOldParams = 99999999; // Updated to defer zerocoin v2 for further testing.

        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nBudgetFeeConfirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x47;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xba;
        vAlertPubKey = ParseHex("04d7e13bc896eb07e2db2d7272f5ddfaedfb64b8ed4caa4d917d6e0781b59ca44f8b5d40995622008e40707b47687eebee11cbe3bbaf2348622cc271c7f0d0bd0a");
        nDefaultPort = 18747;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Curium: 1 day
        nTargetSpacing = 1 * 10;  // Curium: 1 minute
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;
        nLastPOWBlock = 2400;
        nZerocoinStartHeight = 200;

        nZerocoinLastOldParams = 50000;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1526939990;
        genesis.nNonce = 0;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x20438ea808f386bca78de64fc78320312af41d0d828763a9f5dd444d8ba7b54c"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet curium addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet curium script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet curium BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet curium BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet curium BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x01)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();

        bech32_hrp = "tg";

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "040d2595becca91020213bf94735fa26bb92a206aa21be45b0e95f205ff8588ecb9398c5c7d8cfaf78149d230b8dc066c3660573ff2104dac98e43283d6dc882d6"; 
        strObfuscationPoolDummyAddress = "PCYiHgGJJ6xGHqivmdZrYjRnhaYf6AJ2Mp";
        nBudgetFeeConfirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                     // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa2;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Curium: 1 day
        nTargetSpacing = 1 * 60;        // Curium: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1526939990;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 0;
        nMaturity = 0;
        nLastPOWBlock = 999999999; // PoS complicates Regtest because of timing issues
        nZerocoinLastOldParams = 499;
        nZerocoinStartHeight = 100;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18747;
        assert(hashGenesisBlock == uint256("0x20438ea808f386bca78de64fc78320312af41d0d828763a9f5dd444d8ba7b54c"));

        bech32_hrp = "pget";

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
        nRequiredAccumulation = 1;

        // {
        //     "PrivateKey": "923EhWh2bJHynX6d4Tqt2Q75bhTDCT1b4kff3qzDKDZHZ6pkQs7",
        //     "PublicKey": "04866dc02c998b7e1ab16fe14e0d86554595da90c36acb706a4d763b58ed0edb1f82c87e3ced065c5b299b26e12496956b9e5f9f19aa008b5c46229b15477c875a"
        // }
        strSporkKey = "04866dc02c998b7e1ab16fe14e0d86554595da90c36acb706a4d763b58ed0edb1f82c87e3ced065c5b299b26e12496956b9e5f9f19aa008b5c46229b15477c875a";
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 18746;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
