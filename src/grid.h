#ifndef GRID_H
#define GRID_H

#include "object.h"
#include "griddata.h"
#include "gridprogram.h"

class Grid : public Object {
public:
    void setData(std::shared_ptr<GridData> data);
    void setProgram(std::shared_ptr<GridProgram> program);

    std::shared_ptr<GridData> data() const;
    std::shared_ptr<GridProgram> program() const;

    virtual void render() override;

private:
    std::shared_ptr<GridData> m_data;
    std::shared_ptr<GridProgram> m_program;
};

#endif
