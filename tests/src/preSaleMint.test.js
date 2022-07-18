import { processTest, populateTransaction } from "./test.fixture";

const contractName = "NFTExample";

const testLabel = "PreSaleMint"; // <= Name of the test
const testDirSuffix = "pre_sale_mint"; // <= directory to compare device snapshots to
const signedPlugin = false;
const testNetwork= "ethereum";

const contractAddr = "0xd7aff4db67e1aa519807221a09c83ade09833992";
const chainID = 1;

const selector = "0xc111fb91";
const signature = "000000000000000000000000000000000000000000000000000000000000002000000000000000000000000000000000000000000000000000000000000000040010101000000000000000000000000000000000000000000000000000000000"
const value = "18.0";

const inputData = selector + signature;

// Create serializedTx and remove the "0x" prefix
const serializedTx = populateTransaction(contractAddr, inputData, chainID, value);


populateTransaction
const devices = [
  {
    name: "nanos",
    label: "Nano S",
    steps: 4, // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanox",
    label: "Nano X",
    steps: 4, // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanosp",
    label: "Nano S+",
    steps: 4, // <= Define the number of steps for this test case and this device
  },

];

devices.forEach((device) =>{
  processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork);
});