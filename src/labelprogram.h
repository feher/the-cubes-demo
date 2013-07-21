#ifndef LABEL_PROGRAM_H
#define LABEL_PROGRAM_H

#include "program.h"
#include "objectprogram.h"
#include "compasslabel.h"
#include "cursor.h"

class LabelProgram : public Program,
                     public ObjectProgram<CompassLabel>,
                     public ObjectProgram<Cursor> {
public:
    explicit LabelProgram();

    virtual void activate() override;
    virtual void configure(CompassLabel& object) override;
    virtual void configure(Cursor& object) override;
    virtual void cleanup() override;

private:
    template<typename T> void configure(T& object);

    static const std::string vertexShaderFile;
    static const std::string fragmentShaderFile;

    GLint am_vertexPositionId;
    GLint a_vertexUvId;
    GLint u_mvpId;
    GLint u_textureSamplerId;
};

template<typename T>
void LabelProgram::configure(T& object) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, object.programTextureId());

    glUniform1i(u_textureSamplerId, 0);

    const auto& MVP = object.programMvp();
    glUniformMatrix4fv(u_mvpId, 1, GL_FALSE, &MVP[0][0]);

    glEnableVertexAttribArray(am_vertexPositionId);
    glBindBuffer(GL_ARRAY_BUFFER, object.programVertexBufferId());
    glVertexAttribPointer(am_vertexPositionId, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(a_vertexUvId);
    glBindBuffer(GL_ARRAY_BUFFER, object.programUvBufferId());
    glVertexAttribPointer(a_vertexUvId, 2, GL_FLOAT, GL_FALSE, 0, object.programUvOffset());
}

#endif
