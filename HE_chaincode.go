package main

import (
    "encoding/json"
    "fmt"
    "io/ioutil"
    "log"
    "github.com/hyperledger/fabric-contract-api-go/contractapi"
)

type SmartContract struct {
    contractapi.Contract
}

type EncryptedData struct {
    ID            string `json:"id"`
    EncryptedText string `json:"encryptedText"`
}

func (s *SmartContract) InitLedger(ctx contractapi.TransactionContextInterface) error {
    data := []EncryptedData{
        {ID: "data1", EncryptedText: "example_encrypted_data1"},
        {ID: "data2", EncryptedText: "example_encrypted_data2"},
    }

    for _, datum := range data {
        dataJSON, err := json.Marshal(datum)
        if err != nil {
            return err
        }

        err = ctx.GetStub().PutState(datum.ID, dataJSON)
        if err != nil {
            return fmt.Errorf("failed to put data to world state. %v", err)
        }
    }

    return nil
}

func (s *SmartContract) StoreEncryptedData(ctx contractapi.TransactionContextInterface, id string) error {
    // Replace with actual path
    encryptedText, err := ioutil.ReadFile("/path/to/encrypted_data.bin")
    if err != nil {
        log.Fatalf("failed to read encrypted data: %v", err)
    }

    data := EncryptedData{
        ID:            id,
        EncryptedText: string(encryptedText),
    }

    dataJSON, err := json.Marshal(data)
    if err != nil {
        return err
    }

    return ctx.GetStub().PutState(id, dataJSON)
}

func (s *SmartContract) GetEncryptedData(ctx contractapi.TransactionContextInterface, id string) (*EncryptedData, error) {
    dataJSON, err := ctx.GetStub().GetState(id)
    if err != nil {
        return nil, fmt.Errorf("failed to read from world state: %v", err)
    }
    if dataJSON == nil {
        return nil, fmt.Errorf("the data %s does not exist", id)
    }

    var data EncryptedData
    err = json.Unmarshal(dataJSON, &data)
    if err != nil {
        return nil, err
    }

    return &data, nil
}

func main() {
    chaincode, err := contractapi.NewChaincode(new(SmartContract))
    if err != nil {
        fmt.Printf("Error creating chaincode: %v", err)
        return
    }

    if err := chaincode.Start(); err != nil {
        fmt.Printf("Error starting chaincode: %v", err)
    }
}
