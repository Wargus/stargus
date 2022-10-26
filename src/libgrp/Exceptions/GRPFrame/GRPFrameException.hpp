#ifndef GRPFrameException_Header
#define GRPFrameException_Header

#include "../GRPException.hpp"

class GRPFrameException : public GRPException {};
class GRPFrameInvalidFrameDemensions : public GRPFrameException {};
class GRPFrameInvalidImageDemensions : public GRPFrameException {};

#endif