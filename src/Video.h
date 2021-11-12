/*
 * Video.h
 *
 *      Author: Andreas Volz
 */

#ifndef VIDEO_H_
#define VIDEO_H_

// System
#include <memory>

// Forward declarations
class Hurricane;

class Video {
public:
	Video(std::shared_ptr<Hurricane> hurricane);
	virtual ~Video();

	/**
	 *  Convert SMK video to OGV
	 */
	bool ConvertVideo(const std::string &arcfile, const std::string &file);

private:
	std::shared_ptr<Hurricane> mHurricane;
};

#endif /* VIDEO_H_ */
