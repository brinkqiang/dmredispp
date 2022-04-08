
// Copyright (c) 2018 brinkqiang (brink.qiang@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "dmrand.h"

CDMRand::CDMRand()
    : GenerateRand(RandomDevice())
{
    
    
}

uint32_t CDMRand::GetRandRange(uint32_t dwMin, uint32_t dwMax)
{
    std::uniform_int_distribution<uint32_t> _dist(std::min(dwMin, dwMax), std::max(dwMin, dwMax));
    return _dist(GenerateRand);
}

uint32_t CDMRand::GetRand() {
    return GetRandRange(1L, 10000L);
}

bool CDMRand::GetRandHit(float op)
{
    std::bernoulli_distribution _dist(op);
    return _dist(GenerateRand);
}

