#ifndef BITMAP_H
#define BITMAP_H

#include <fstream>
#include <cmath>
#include "Vector.h"
#include "Color.h"

namespace Graphics {
    enum Channel {
        R = 2,
        G = 1,
        B = 0
    };

    enum RotateAngle {
        D90 = 0,
        D180 = 1,
        D270 = 2
    };

    enum Offsets {
        TYPE = 0x00,
        FILE_SIZE = 0x02,
        IMG_OFFSET = 0x0A,
        INFO_SIZE = 0x00,
        WIDTH = 0x04,
        HEIGHT = 0x08,
        DEPTH = 0x0E,
        HEIGHT_CORE = 0x06,
        DEPTH_CORE = 0x0A
    };

    extern const Mat2D rotation[3];

    class BitMap {
    protected:
        static const int AVAILABLE_DEPTH = 24;
        static const int HEADER_SIZE = 14;
        static const int CORE_VERSION_SIZE = 12;

        byte header[HEADER_SIZE], *data = nullptr, *img;
        int16_t type;
        int32_t fileSize, imgOffset, dataSize;
        int32_t infoSize, width, height, paddingWidth;
        int16_t depth;
        Vec2D end;
        std::string name;

    public:
        BitMap() = default;

        BitMap(const BitMap &bm) = default;

        void copy(BitMap &cp);

        ~BitMap();

        int32_t getFileSize() const;

        int32_t getInfoSize() const;

        int32_t getWidth() const;

        int32_t getHeight() const;

        int16_t getDepth() const;

        const std::string &getName() const;

        void clear();

        bool empty();

        void read(std::string name) noexcept(false);

        void save(std::string name) noexcept(false);

        BitMap(std::string name) noexcept(false);

        int getPixelPos(Vec2D pos) noexcept(false);

        int getChannel(Vec2D pos, Channel channel) noexcept(false);

        void setChannel(Vec2D pos, Channel channel, int val) noexcept(false);

        Color getPixel(Vec2D pos) noexcept(false);

        void setPixel(Vec2D pos, Color color) noexcept(false);

        void drawLine(Vec2D p1, Vec2D p2, Color color = BLACK, int wd = 0) noexcept;

        void drawRect(Vec2D p1, Vec2D p2, Color color = BLACK, int wd = 0, bool fill = false,
                      Color fillColor = BLACK) noexcept;

        void drawCrossRect(Vec2D p1, Vec2D p2, Color color = BLACK, int wd = 0, bool fill = false,
                           Color fillColor = BLACK) noexcept;

        void filter(Channel c, int val) noexcept;

        void drawCircle(Vec2D c, int r, Color color = BLACK, int wd = 0, bool fill = false,
                        Color fillColor = BLACK) noexcept;

        void rotate(Vec2D p1, Vec2D p2, RotateAngle a) noexcept;


        void uploadToData();

        BitMap(Vec2D size, BitMap &infoSrc);

        static Vec2D getSizeToRot(Vec2D end, RotateAngle a);

        static Vec2D transformToRot(Vec2D p, Vec2D end, RotateAngle a);

        void fullRotate(BitMap &dest, RotateAngle a);

        void fullRotate(RotateAngle a);
    };
}
#endif //BITMAP_H
