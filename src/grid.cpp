#include "grid.h"

using namespace std;

void Grid::setData(shared_ptr<GridData> data) {
    m_data = data;
}
void Grid::setProgram(shared_ptr<GridProgram> program) {
    m_program = program;
}

shared_ptr<GridData> Grid::data() const {
    return m_data;
}

shared_ptr<GridProgram> Grid::program() const {
    return m_program;
}

void Grid::render() {
    // Set up the program
    m_program->activate();

    const auto& M = modelMatrix();
    const auto& V = camera()->viewMatrix();
    const auto& P = *projectionMatrix();
    auto MVP = P * V * M;
    auto c = color();

    glUniform4fv(m_program->u_colorId, 1, &c[0]);
    glUniformMatrix4fv(m_program->u_mvpId, 1, GL_FALSE, &MVP[0][0]);

    glEnableVertexAttribArray(m_program->am_vertexPositionId);
    glBindBuffer(GL_ARRAY_BUFFER, m_data->vertexBufferId);
    glVertexAttribPointer(m_program->am_vertexPositionId, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Draw
    viewport()->activate();
    glLineWidth(m_data->lineWidth);
    glDrawArrays(GL_LINES, 0, m_data->vertexCount);

    // Done
    glDisableVertexAttribArray(m_program->am_vertexPositionId);
}
