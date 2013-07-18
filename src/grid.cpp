#include "grid.h"

using namespace std;

void Grid::setData(shared_ptr<const GridData> data) {
    m_data = data;
}
void Grid::setProgram(shared_ptr<ObjectProgram<Grid>> program) {
    m_program = program;
}

void Grid::render() {
    m_program->activate();
    m_program->configure(*this);

    viewport()->activate();
    glLineWidth(m_data->lineWidth);
    glDrawArrays(GL_LINES, 0, m_data->vertexCount);

    m_program->cleanup();
}
