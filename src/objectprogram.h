#ifndef OBJECT_PROGRAM_H
#define OBJECT_PROGRAM_H

// This template is used to tag an ObjectProgram to indicate the kind
// of Object it can be applied to. Thanks to multiple inheritance,
// an ObjectProgram can apply to multiple Object types.
template <typename O>
class ObjectProgram
{
public:
    virtual void activate() = 0;
    virtual void configure(O& object) = 0;
    virtual void cleanup() = 0;
};

#endif
