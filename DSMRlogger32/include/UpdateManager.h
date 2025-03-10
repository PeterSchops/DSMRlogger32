#pragma once
/*
** See MIT license at the end of this file
*/

#include <Arduino.h>
#include <ArduinoOTA.h>


typedef std::function<void(u_int8_t progress)> ProgressCallback;

class UpdateManager {
  public:
    enum updateFeedback {
      UPDATE_FEEDBACK_OK = 0,
	  UPDATE_FEEDBACK_UPDATE_OK = 1,
	  UPDATE_FEEDBACK_UPDATE_ERROR = 2
    };
	enum class update {
	  FIRMWARE, 
	  SPIFFS
	};
  
	UpdateManager();
	void setProgressCallback(ProgressCallback callback);
    bool feedback(int8_t);
	void updateFirmware(const char *url, ProgressCallback callback = nullptr);
    void updateSpiffs(const char *url, ProgressCallback callback = nullptr);

  private:
	int 	  _lastOtaCommand;
    int8_t  _feedback;

	ProgressCallback _progressCallback;
	u_int8_t _lastPercentage;
	const char *_url;
	void startUpdate();
	void onStart();
	void onProgress(unsigned int progress, unsigned int total);
	void onEnd();
	void onError(ota_error_t error);
	bool httpUpdate(update data, const char *url);
};

/**********************************************************************************
 * MIT License
 *
 * Copyright (c) 2024 Willem Aandewiel (mrWheel)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 **********************************************************************************
*/
