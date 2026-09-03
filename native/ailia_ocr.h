/**
 * \~japanese
 * @file ailia_ocr.h
 * @brief ailia OCR  AI OCRライブラリ
 * @copyright ax Inc.
 * @date 2024/7/8
 */

#ifndef INCLUDE_AILIA_OCR
#define INCLUDE_AILIA_OCR

#include <wchar.h>
#include "ailia.h"

/* 呼び出し規約 */

#if defined(_WIN64) || defined(_M_X64) || defined(__amd64__) || defined(__x86_64__) || defined(__APPLE__) || \
	defined(__ANDROID__) || defined(ANDROID) || defined(__linux__) || defined(NN_NINTENDO_SDK)
#define AILIA_API
#else
#define AILIA_API __stdcall
#endif

#if defined(_WIN32) && !defined(_WIN64)
	#define AILIA_OCR_USER_API __stdcall
#else
	#define AILIA_OCR_USER_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define AILIA_OCR_CALLBACK_VERSION (1)

#define AILIA_OCR_RESULT_VERSION (1)

typedef int(AILIA_OCR_USER_API* AILIA_OCR_USER_API_AILIA_CREATE)(struct AILIANetwork **, int, int);
typedef int(AILIA_OCR_USER_API* AILIA_OCR_USER_API_AILIA_OPEN_WEIGHT_FILE_A)(struct AILIANetwork *, const char *);
typedef int(AILIA_OCR_USER_API* AILIA_OCR_USER_API_AILIA_OPEN_WEIGHT_FILE_W)(struct AILIANetwork *, const wchar_t *);
typedef int(AILIA_OCR_USER_API* AILIA_OCR_USER_API_AILIA_OPEN_STREAM_FILE_A)(struct AILIANetwork *, const char *);
typedef int(AILIA_OCR_USER_API* AILIA_OCR_USER_API_AILIA_OPEN_STREAM_FILE_W)(struct AILIANetwork *, const wchar_t *);
typedef int(AILIA_OCR_USER_API* AILIA_OCR_USER_API_AILIA_OPEN_WEIGHT_MEM)(struct AILIANetwork *, const void *, unsigned int);
typedef int(AILIA_OCR_USER_API* AILIA_OCR_USER_API_AILIA_SET_MEMORY_MODE)(struct AILIANetwork*, unsigned int);
typedef void(AILIA_OCR_USER_API* AILIA_OCR_USER_API_AILIA_DESTROY)(struct AILIANetwork *);
typedef int(AILIA_OCR_USER_API* AILIA_OCR_USER_API_AILIA_UPDATE)(struct AILIANetwork *);
typedef int(AILIA_OCR_USER_API* AILIA_OCR_USER_API_AILIA_GET_BLOB_INDEX_BY_INPUT_INDEX)(struct AILIANetwork *, unsigned int *, unsigned int);
typedef int(AILIA_OCR_USER_API* AILIA_OCR_USER_API_AILIA_GET_BLOB_INDEX_BY_OUTPUT_INDEX)(struct AILIANetwork *, unsigned int *, unsigned int);
typedef int(AILIA_OCR_USER_API* AILIA_OCR_USER_API_AILIA_GET_BLOB_DATA)(struct AILIANetwork *, void*, unsigned int, unsigned int);
typedef int(AILIA_OCR_USER_API* AILIA_OCR_USER_API_AILIA_SET_INPUT_BLOB_DATA)(struct AILIANetwork *, const void*, unsigned int, unsigned int);
typedef int(AILIA_OCR_USER_API* AILIA_OCR_USER_API_AILIA_SET_INPUT_BLOB_SHAPE)(struct AILIANetwork *, const AILIAShape*, unsigned int, unsigned int);
typedef int(AILIA_OCR_USER_API* AILIA_OCR_USER_API_AILIA_GET_BLOB_SHAPE)(struct AILIANetwork *, AILIAShape*, unsigned int, unsigned int);
typedef const char*(AILIA_OCR_USER_API* AILIA_OCR_USER_API_AILIA_GET_ERROR_DETAIL)(struct AILIANetwork *);
typedef int(AILIA_OCR_USER_API* AILIA_OCR_USER_API_AILIA_COPY_BLOB_DATA)(struct AILIANetwork* dst_net, unsigned int dst_blob_idx, struct AILIANetwork* src_net, unsigned int src_blob_idx);
typedef int (AILIA_OCR_USER_API* AILIA_OCR_USER_API_AILIA_GET_ENVIRONMENT)(AILIAEnvironment** env, unsigned int env_idx, unsigned int version);


typedef struct _AILIAOcrApiCallback {
	AILIA_OCR_USER_API_AILIA_CREATE ailiaCreate;
	AILIA_OCR_USER_API_AILIA_OPEN_WEIGHT_FILE_A ailiaOpenWeightFileA;
	AILIA_OCR_USER_API_AILIA_OPEN_WEIGHT_FILE_W ailiaOpenWeightFileW;
	AILIA_OCR_USER_API_AILIA_OPEN_STREAM_FILE_A ailiaOpenStreamFileA;
	AILIA_OCR_USER_API_AILIA_OPEN_STREAM_FILE_W ailiaOpenStreamFileW;
	AILIA_OCR_USER_API_AILIA_OPEN_WEIGHT_MEM ailiaOpenWeightMem;
	AILIA_OCR_USER_API_AILIA_SET_MEMORY_MODE ailiaSetMemoryMode;
	AILIA_OCR_USER_API_AILIA_DESTROY ailiaDestroy;
	AILIA_OCR_USER_API_AILIA_UPDATE ailiaUpdate;
	AILIA_OCR_USER_API_AILIA_GET_BLOB_INDEX_BY_INPUT_INDEX ailiaGetBlobIndexByInputIndex;
	AILIA_OCR_USER_API_AILIA_GET_BLOB_INDEX_BY_OUTPUT_INDEX ailiaGetBlobIndexByOutputIndex;
	AILIA_OCR_USER_API_AILIA_GET_BLOB_DATA ailiaGetBlobData;
	AILIA_OCR_USER_API_AILIA_SET_INPUT_BLOB_DATA ailiaSetInputBlobData;
	AILIA_OCR_USER_API_AILIA_SET_INPUT_BLOB_SHAPE ailiaSetInputBlobShape;
	AILIA_OCR_USER_API_AILIA_GET_BLOB_SHAPE ailiaGetBlobShape;
	AILIA_OCR_USER_API_AILIA_GET_ERROR_DETAIL ailiaGetErrorDetail;
	AILIA_OCR_USER_API_AILIA_COPY_BLOB_DATA ailiaCopyBlobData;
	AILIA_OCR_USER_API_AILIA_GET_ENVIRONMENT ailiaGetEnvironment;
} AILIAOcrApiCallback;

struct AILIAOcr;

/**
 * \* japanese
 * @brief OCRの結果を表す構造体
 * \* english
 * @brief Structure representing the result of OCR
 */
typedef struct _AILIAOcrResult {
  int xmin;
  int xmax;
  int ymin;
  int ymax;
  const char* text;
  float score;
} AILIAOcrResult;

/**
 * \* japanese
 * @brief OCRネットワークを作成します。
 * @param net ネットワークオブジェクトのポインタへのポインタ
 * @param env_id 環境ID ( ailiaGetEnvironment() で取得)  \ref AILIA_ENVIRONMENT_ID_AUTO にした場合は自動で選択する
 * @param num_thread スレッド数の上限(  \ref AILIA_MULTITHREAD_AUTO  にした場合は自動で設定)
 * @param memory_mode メモリモード(AILIA_MEMORY_MODE_*)
 * @param callback ailiaのAPIへのコールバック
 * @param version AILIA_OCR_CALLBACK_VERSION
 * @return
 *  成功した場合は \ref AILIA_STATUS_SUCCESS 、そうでなければエラーコードを返す。
 * @details
 *  ネットワークオブジェクトを作成します
 * \* english
 * @brief Create OCR network.
 * @param net Pointer to pointer of network object
 * @param env_id The ID of the inference backend used for computation (obtained by  ailiaGetEnvironment() ). It is selected automatically if  \ref AILIA_ENVIRONMENT_ID_AUTO  is specified.
 * @param num_thread The upper limit on the number of threads (It is set automatically if  \ref AILIA_MULTITHREAD_AUTO
 * @param memory_mode The memory mode (AILIA_MEMORY_MODE_*)
 * @param callback The callback for ailia API
 * @param version AILIA_OCR_CALLBACK_VERSION
 * @return
 *   If this function is successful, it returns  \ref AILIA_STATUS_SUCCESS , or an error code otherwise.
 * @details
 *   Creates a network instance.
 */
int AILIA_API ailiaOcrCreate(
  struct AILIAOcr** net, 
  int env_id, 
  int num_thread, 
  int memory_mode, 
  AILIAOcrApiCallback callback,
  int version
);

/**
 * \* japanese
 * @brief OCRの文字の検出のタスクを行うネットワークを初期化します。
 * @param net OCRネットワークオブジェクトへのポインタ
 * @param weight_path weightファイルのパス
 * @param db_threshold 文字の検出の閾値
 * @param db_box_threshold バウンディングボックスにその点が含まれるかどうかの閾値
 * @param db_unclip_ratio バウンディングボックスの閾値
 * @param det_limit_type 検出の制限タイプ { "max" or "min" }
 * @param det_limit_side_len 検出の制限サイド長
 * @param normalize_scale 正規化のスケール
 * @param normalize_mean 正規化の平均
 * @param normalize_std 正規化の標準偏差
 * @return
 *  成功した場合は \ref AILIA_STATUS_SUCCESS 、そうでなければエラーコードを返す。
 * @details
 * OCRの文字の検出のタスクを行うネットワークを初期化します。
 * \* english
 * @brief Initialize the network for OCR detection task.
 * @param net Pointer to OCR network object
 * @param weight_path Path of weight file
 * @param db_threshold Threshold of DB
 * @param db_box_threshold Threshold of DB box
 * @param db_unclip_ratio Unclip ratio of DB
 * @param det_limit_type Limit type of detection { "max" or "min" }
 * @param det_limit_side_len Limit side length of detection
 * @param normalize_scale Scale of normalization
 * @param normalize_mean Mean of normalization
 * @param normalize_std Standard deviation of normalization
 * @return
 *  If this function is successful, it returns  \ref AILIA_STATUS_SUCCESS , or an error code otherwise.
 * @details
 * Initialize the network for OCR detection task.
 */
int AILIA_API ailiaOcrInitializeDetectorA(
  struct AILIAOcr * net,
  const char* weight_path,
  float db_threshold,
  float db_box_threshold,
  float db_unclip_ratio,
  const char* det_limit_type,
  int det_limit_side_len,
  float normalize_scale,
  float normalize_mean[3],
  float normalize_std[3]
);

int AILIA_API ailiaOcrInitializeDetectorW(
  struct AILIAOcr * net,
  const wchar_t* weight_path,
  float db_threshold,
  float db_box_threshold,
  float db_unclip_ratio,
  const char* det_limit_type,
  int det_limit_side_len,
  float normalize_scale,
  float normalize_mean[3],
  float normalize_std[3]
);

/** 
 * \* japanese
 * @brief OCRの文字の分類のタスクを行うネットワークを初期化します。
 * @param net OCRネットワークオブジェクトへのポインタ
 * @param cls_post_process_label_list 分類の後処理のラベルリスト
 * @param weight_path weightファイルのパス
 * @param channel 画像のチャンネル数
 * @param width 画像の幅
 * @param height 画像の高さ
 * @param bach_num classifierで推論するバッチ数
 * @param threshold 分類の閾値
 * @return
 * 成功した場合は \ref AILIA_STATUS_SUCCESS 、そうでなければエラーコードを返す。
 * @details
 * OCRの文字の分類のタスクを行うネットワークを初期化します。
 * \* english
 * @brief Initialize the network for OCR classification task.
 * @param net Pointer to OCR network object
 * @param cls_post_process_label_list Label list of post process of classification
 * @param weight_path Path of weight file
 * @param channel Channel of image
 * @param width Width of image
 * @param height Height of image
 * @param bach_num Batch number of classifier
 * @param threshold Threshold of classification
 * @return
 * If this function is successful, it returns  \ref AILIA_STATUS_SUCCESS , or an error code otherwise.
 * @details
 * Initialize the network for OCR classification task.
 */
int AILIA_API ailiaOcrInitializeClassifierA(
  struct AILIAOcr * net,
  int cls_post_process_label_list[2],
  const char* weight_path,
  int channel,
  int width,
  int height,
  int bach_num,
  float threshold
);

int AILIA_API ailiaOcrInitializeClassifierW(
  struct AILIAOcr * net,
  int cls_post_process_label_list[2],
  const wchar_t* weight_path,
  int channel,
  int width,
  int height,
  int bach_num,
  float threshold
);

/** 
 * \* japanese
 * @brief OCRの文字の認識のタスクを行うネットワークを初期化します。
 * @param net OCRネットワークオブジェクトへのポインタ
 * @param weight_path weightファイルのパス
 * @param dict_path 辞書ファイルのパス
 * @param limit_max_width 認識の制限の最大幅
 * @param limit_min_width 認識の制限の最小幅
 * @param rec_image_shape 認識の画像の形状
 * @param char_type 文字の種類
 * @param batch_num 認識で推論するバッチ数
 * @param rec_batch_num 認識で推論するバッチ数
 * @return
 * 成功した場合は \ref AILIA_STATUS_SUCCESS 、そうでなければエラーコードを返す。
 * @details
 * OCRの文字の認識のタスクを行うネットワークを初期化します。
 * \* english
 * @brief Initialize the network for OCR recognition task.
 * @param net Pointer to OCR network object
 * @param weight_path Path of weight file
 * @param dict_path Path of dictionary file
 * @param limit_max_width Limit max width of recognition
 * @param limit_min_width Limit min width of recognition
 * @param rec_image_shape Shape of recognition image
 * @param char_type Type of character
 * @param batch_num Batch number of recognition
 * @param rec_batch_num Batch number of recognition
 * @return
 * If this function is successful, it returns  \ref AILIA_STATUS_SUCCESS , or an error code otherwise.
 * @details
 * Initialize the network for OCR recognition task.
 */
int AILIA_API ailiaOcrInitializeRecognizerA(
  struct AILIAOcr * net,
  const char* weight_path,
  const char* dict_path,
  int limit_max_width,
  int limit_min_width,
  int rec_image_shape[3],
  const char* char_type,
  int batch_num,
  int rec_batch_num
);

int AILIA_API ailiaOcrInitializeRecognizerW(
  struct AILIAOcr * net,
  const wchar_t* weight_path,
  const wchar_t* dict_path,
  int limit_max_width,
  int limit_min_width,
  int rec_image_shape[3],
  const char* char_type,
  int batch_num,
  int rec_batch_num
);

/**
 * \* japanese
 * @brief OCRの計算を行います。
 * @param ailiaOcr OCRネットワークオブジェクトへのポインタ
 * @param data 画像データ channelが3の場合はRGB (CHANNEL_LAST) の順番で入力を行ってください。dataのレンジは0~255です
 * @param width 画像の幅
 * @param height 画像の高さ
 * @param channel 画像のチャンネル数
 * @return
 * 成功した場合は \ref AILIA_STATUS_SUCCESS 、そうでなければエラーコードを返す。
 * @details
 * OCRの計算を行います。
 * 計算結果は次の`ailiaOcrCompute`を呼び出すまで保持されます。
 * \* english
 * @brief Calculate OCR.
 * @param ailiaOcr Pointer to OCR network object
 * @param data Image data. If channel is 3, please input RGB (CHANNEL_LAST) order. The range of data is 0~255.
 * @param width Width of image
 * @param height Height of image
 * @param channel Channel of image
 * @return
 * If this function is successful, it returns  \ref AILIA_STATUS_SUCCESS , or an error code otherwise.
 * @details
 * Calculate OCR.
 * The calculation result is held until the next `ailiaOcrCompute` is called.
 */
int AILIA_API ailiaOcrCompute(
  struct AILIAOcr* ailiaOcr,
  const float* data,
  int width,
  int height,
  int channel);

// void AILIA_API ailiaOcrGetOutputData(
//   struct AILIAOcr* net, AILIAOcrResult** result, int& result_num);


/**
 * \* japanese
 * @brief OCRで検出された文字列の数を取得します。
 * @param ailiaOcr OCRネットワークオブジェクトへのポインタ
 * @param result_num OCRで検出された文字列の数の参照
 * @return
 * 成功した場合は \ref AILIA_STATUS_SUCCESS 、そうでなければエラーコードを返す。
 * @details
 * OCRで検出された文字列の数を取得します。
 * \* english
 * @brief Get the number of strings detected by OCR.
 * @param ailiaOcr Pointer to OCR network object
 * @param result_num Reference of the number of strings detected by OCR
 */
int AILIA_API ailiaOcrGetResultNum(
  struct AILIAOcr* ailiaOcr,
  unsigned int* result_num);

/**
 * \* japanese
 * @brief OCRで検出された文字列の情報を取得します。
 * @param ailiaOcr OCRネットワークオブジェクトへのポインタ
 * @param result OCRで検出された文字列の情報の参照
 * @param idx OCRで検出された文字列のインデックス
 * @param version AILIA_OCR_RESULT_VERSIONを指定してください
 * @return
 * 成功した場合は \ref AILIA_STATUS_SUCCESS 、そうでなければエラーコードを返す。
 * @details
 * OCRで検出された文字列の情報を取得します。
 * resultの中に存在するconst char*の寿命は次のaiiliaOcrComputeが呼ばれるまでです。
 * \* english
 * @brief Get the information of the string detected by OCR.
 * @param ailiaOcr Pointer to OCR network object
 * @param result Reference of the information of the string detected by OCR
 * @param idx Index of the string detected by OCR
 * @param version Please specify AILIA_OCR_RESULT_VERSION
 * @return
 * If this function is successful, it returns  \ref AILIA_STATUS_SUCCESS , or an error code otherwise.
 * @details
 * Get the information of the string detected by OCR.
 * The lifetime of const char* in result is until the next aiiliaOcrCompute is called.
 */
int AILIA_API ailiaOcrGetResult(
  struct AILIAOcr* ailiaOcr,
  AILIAOcrResult* result,
  unsigned int idx,
  int version
);

/**
 * \* japanese
 * @brief OCRで発生したエラーの内容を取得します。
 * @param ailiaOcr OCRネットワークオブジェクトへのポインタ
 * @return
 * エラーの文字列のポインタを返します。
 * @details
 * OCRで発生したエラーの内容を取得します。
 * \* english
 * @brief Get the error message of OCR.
 * @param ailiaOcr Pointer to OCR network object
 * @param error Pointer to the error message of OCR
 * @return
 * Error message of OCR.
 * @details
 * Get the error message of OCR.
 * The lifetime of the pointer is until the next ailiaOcr API is called.
 */
const char* AILIA_API ailiaOcrGetErrorDetail(
  struct AILIAOcr* ailiaOcr);

/**
 * \* japanese
 * @brief OCRのネットワークオブジェクトを破棄します。
 * @param ailiaOcr OCRネットワークオブジェクトへのポインタ
 * @return
 * 成功した場合は \ref AILIA_STATUS_SUCCESS 、そうでなければエラーコードを返す。
 * @details
 * OCRのネットワークオブジェクトを破棄します。
 * \* english
 * @brief Destroy OCR network object.
 * @param ailiaOcr Pointer to OCR network object
 * @return
 * If this function is successful, it returns  \ref AILIA_STATUS_SUCCESS , or an error code otherwise.
 * @details
 * Destroy OCR network object.
 */
int AILIA_API ailiaOcrDestroy(
  struct AILIAOcr* ailiaOcr);


#ifdef __cplusplus
}
#endif

#endif
