/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021 Silverlan
 */

#ifndef __PANIMA_POSE_HPP__
#define __PANIMA_POSE_HPP__

#include "panima/types.hpp"
#include <mathutil/transform.hpp>

namespace panima {
	class Pose {
	  public:
		Pose() = default;
		Pose(const Pose &) = default;
		Pose(Pose &&) = default;
		Pose(const std::vector<umath::ScaledTransform> &transforms);
		Pose(std::vector<umath::ScaledTransform> &&transforms);
		Pose &operator=(const Pose &) = default;
		Pose &operator=(Pose &&) = default;
		bool operator==(const Pose &other) const { return m_transforms == other.m_transforms; }
		bool operator!=(const Pose &other) const { return !operator==(other); }
		const std::vector<umath::ScaledTransform> &GetTransforms() const { return const_cast<Pose *>(this)->GetTransforms(); }
		std::vector<umath::ScaledTransform> &GetTransforms() { return m_transforms; }
		void SetTransformCount(uint32_t c);
		void SetBoneIndex(uint32_t channelId, BoneId boneId);
		umath::ScaledTransform *GetTransform(BoneId idx);
		const umath::ScaledTransform *GetTransform(BoneId idx) const { return const_cast<Pose *>(this)->GetTransform(idx); }
		void SetTransform(BoneId idx, const umath::ScaledTransform &pose);
		void Clear();
		void Lerp(const Pose &other, float f);
		operator bool() const { return !m_transforms.empty(); }

		void Localize(const panima::Skeleton &skeleton);
		void Globalize(const panima::Skeleton &skeleton);

		std::vector<uint32_t> &GetBoneTranslationTable() { return m_boneIdToChannelId; }
		const std::vector<uint32_t> &GetBoneTranslationTable() const { return const_cast<Pose *>(this)->GetBoneTranslationTable(); }
	  private:
		uint32_t GetChannelIdx(BoneId boneId) const;
		std::vector<umath::ScaledTransform> m_transforms {};
		std::vector<uint32_t> m_boneIdToChannelId;
		Skeleton *m_skeleton;
	};
};
std::ostream &operator<<(std::ostream &out, const panima::Pose &o);

#endif
