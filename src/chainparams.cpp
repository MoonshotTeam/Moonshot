// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

const string CChainParams::MAIN = "main";
const string CChainParams::TESTNET = "test";
const string CChainParams::REGTEST = "regtest";

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        strDataDir = "";
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x49;
        pchMessageStart[1] = 0x4e;
        pchMessageStart[2] = 0x43;
        pchMessageStart[3] = 0x50;

        vAlertPubKey = ParseHex("04aaffe2833752dcc3d98f335e9153237fa5aba5fa2d1d90090156c141535a3fc7bc671f83a754e11ab96311b1eb036b56fa2be9e03a1fe17b5074f54e21800836");
        nDefaultPort = 13766;
        nRPCPort = 13767;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 14);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 14);

        const char* pszTimestamp = "September 25, 2016 - Moonshot Launch";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1474797346, vin, vout, 0);

        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1474797346;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 12;
		

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x000201ad21c6c3bd77a4f1d06568d075e7f6a556c3b18e0b5cc246a0c44ee1e3"));
        assert(genesis.hashMerkleRoot == uint256("0xa0d13ce15d6b5ef12de55d2d5778b702c8c146bb42a3c05a03af868b8ba45c5b"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(51);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(112);
        base58Prefixes[SECRET_KEY] =     list_of(202);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nTargetSpacing = 60;
        nTargetTimespan = 10 * nTargetSpacing;
        nLastPoWBlock = 2880;
        nFirstPoSBlock = 120;

        nProofOfStakeReward = 10 * CENT; // 10%
        nModifierInterval = 10 * 60;  // time to elapse before new modifier is computed
        nStakeMinAge = 1 * 60 * 60;   // 1 Hour
        nStakeMaxAge = -1;  // Unlimited

        nCoinbaseMaturity = 120;

    }

    virtual const CBlock& GenesisBlock() const { return genesis; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        strNetworkID = "testnet";
        strDataDir = "testnet";
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x49;
        pchMessageStart[1] = 0x4e;
        pchMessageStart[2] = 0x43;
        pchMessageStart[3] = 0x54;

        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 16);

        vAlertPubKey = ParseHex("04e44761e96c9056be6b659c04b94fbfebeb5d5257fe028e80695c62f7c2f81f85d131a669df3be611393f454852a2d08c6314aad5ca3cbe5616262db3d4a6efac");
        nDefaultPort = 17100;
        nRPCPort = 17101;

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 344590;

        hashGenesisBlock = genesis.GetHash();

        // assert(hashGenesisBlock == uint256("0x"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(128);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(208);
        base58Prefixes[SECRET_KEY]     = list_of(234);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nTargetSpacing = 10;
        nLastPoWBlock = 0x7fffffff;
        nFirstPoSBlock = 1080;

        nProofOfStakeReward = 10 * CENT; // 10%
        nModifierInterval = 10 * 60; // time to elapse before new modifier is computed
        nStakeMinAge = 1 * 60 * 60;  // 1 hour
        nStakeMaxAge = 8 * 60 * 60;  // 8 hour

        nCoinbaseMaturity = 60;
    }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        strDataDir = "regtest";

        pchMessageStart[0] = 0x49;
        pchMessageStart[1] = 0x4e;
        pchMessageStart[2] = 0x43;
        pchMessageStart[3] = 0x51;

        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1462510800;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 3248;
        nDefaultPort = 17200;
        nRPCPort = 17201;

        hashGenesisBlock = genesis.GetHash();

        // assert(hashGenesisBlock == uint256("0x"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(const string &chain) {
    if (chain == CChainParams::MAIN)
        pCurrentParams = &mainParams;
    else if (chain == CChainParams::TESTNET)
        pCurrentParams = &testNetParams;
    else if (chain == CChainParams::REGTEST)
        pCurrentParams = &regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

const CChainParams &Params(const std::string& chain) {
    if (chain == CChainParams::MAIN)
            return mainParams;
    else if (chain == CChainParams::TESTNET)
            return testNetParams;
    else if (chain == CChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
