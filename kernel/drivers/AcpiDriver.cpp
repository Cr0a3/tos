#include <drivers/AcpiDriver.hpp>
#include <drivers/IoDriver.hpp>
#include <drivers/SerialDriver.hpp>
#include <panic.hpp>

extern "C" {
    #include <limine.h>
    #include <string.h>
}

bool doACPIHeaderChecksum(ACPISDTHeader *tableHeader)
{
    unsigned char sum = 0;
 
    for (int i = 0; i < tableHeader->Length; i++)
    {
        sum += ((char *) tableHeader)[i];
    }
 
    return sum == 0;
}

acpiDriver::acpiDriver() {}

static volatile struct limine_rsdp_request rsdp_request = {
    .id = LIMINE_RSDP_REQUEST,
    .revision = 0
};

void acpiDriver::getRSDT() {
    if (rsdp_request.response == NULL) {
        panic("could not get rsdp");
    }

    limine_rsdp_response *response = rsdp_request.response;

    
    RSDP_t* rsdp = (RSDP_t*)response->address;

    if (rsdp->Revision == 0) {  // acpi version 1.0
        

        //make test

        if ( !doACPIHeaderChecksum(&((RSDT*)rsdp->RsdtAddress)->h) ) {
            panic("rsdt has an invalid checksum");
        }


        this->rsdp = rsdp;
        this->rsdp_b = true;
        this->xsdp_b = true;
    }

    else {

        XSDP_t* xsdp = (XSDP_t*)response->address;

        if ( !doACPIHeaderChecksum(&((RSDT*)rsdp->RsdtAddress)->h) ) {
            panic("rsdt has an invalid checksum");
        }

        if ( !doACPIHeaderChecksum(&((XSDT*)xsdp->XsdtAddress)->h) ) {
            panic("xsdt has an invalid checksum");
        }

        this->rsdp = rsdp;
        this->xsdp = xsdp;

        this->xsdp_b = true;
    }
}

void acpiDriver::getTables() {
    RSDT* rsdt = (RSDT*)this->rsdp->RsdtAddress;
    int entries = (rsdt->h.Length - sizeof(rsdt->h)) / 4;

    void* fadt = NULL;
    void* madt = NULL;

    for (int i = 0; i < entries; i++) {
        ACPISDTHeader* header = (ACPISDTHeader*)rsdt->PointerToOtherSDT[i];
        if (strncmp(header->Signature, "FACP", 4) == 0) {  //found fadt
            fadt = (void*)header;
        }

        if (strncmp(header->Signature, "APIC", 4) == 0) {  //found madt
            madt = (void*)madt;
        }
    }
}

void acpiDriver::getFADT() {
    this->fadt = ( FADT* )this->fadtp;
}

void acpiDriver::init() {
    this->getRSDT();
    this->getTables();
    this->getFADT();

    // enabiling acpi
    //IoDriver.outb(this->fadt->SMI_CommandPort, this->fadt->AcpiEnable); // stops
    //while (IoDriver.inw(this->fadt->PM1aControlBlock) & 1 == 0);
}

void acpiDriver::shutdown() {
    panic("acpi shutdown failed");
}

void acpiDriver::restart() {
    panic("acpi restart failed");
}

extern acpiDriver AcpiDriver = acpiDriver();