#include "idtload.h"
IDTEntry g_IDT[256];

IDTDescriptor g_IDTDescriptor = { sizeof(g_IDT) - 1, g_IDT };

void i686_IDT_SetGate(int interrupt, void* base, uint16_t segmentDescriptor, uint8_t flags)
{
    g_IDT[interrupt].BaseLow = ((uint32_t)base) & 0xFFFF;
    g_IDT[interrupt].SegmentSelector = segmentDescriptor;
    g_IDT[interrupt].Reserved = 0;
    g_IDT[interrupt].Flags = flags;
    g_IDT[interrupt].BaseHigh = ((uint32_t)base >> 16) & 0xFFFF;
}



void IDT_SetGATE(int interrupt, void* base)
{
    g_IDT[interrupt].BaseLow = ((uint32_t)base) & 0xFFFF;
    g_IDT[interrupt].SegmentSelector = 0x08;
    g_IDT[interrupt].Reserved = 0;
    g_IDT[interrupt].Flags = 0x8E;
    g_IDT[interrupt].BaseHigh = ((uint32_t)base >> 16) & 0xFFFF;
}




void i686_IDT_EnableGate(int interrupt)
{
    FLAG_SET(g_IDT[interrupt].Flags, IDT_FLAG_PRESENT);
}

void i686_IDT_DisableGate(int interrupt)
{
    FLAG_UNSET(g_IDT[interrupt].Flags, IDT_FLAG_PRESENT);
}

void i686_IDT_Initialize()
{
    i686_IDT_Load(&g_IDTDescriptor);
}