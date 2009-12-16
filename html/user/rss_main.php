<?php
// This file is part of BOINC.
// http://boinc.berkeley.edu
// Copyright (C) 2008 University of California
//
// BOINC is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// BOINC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with BOINC.  If not, see <http://www.gnu.org/licenses/>.

require_once("../project/project.inc");
require_once("../inc/forum_rss.inc");

if (defined("NEWS_FORUM_NAME")) {
    $forum_name = NEWS_FORUM_NAME;
} else {
    $forum_name = "News";
}
$forum = BoincForum::lookup("parent_type=0 and title = '$forum_name'");
if (!$forum) {
    exit;
}

forum_rss($forum->id, 0, 0, 1, 9999);
?>
