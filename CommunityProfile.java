import java.util.ArrayList;
import java.util.List;

public class CommunityProfile {
    private String id;
    private String nickname;
    private String joinedDate;
    private List<String> friends;
    private List<String> badges;

    public CommunityProfile() {
        this.friends = new ArrayList<>();
        this.badges = new ArrayList<>();
    }

    public CommunityProfile(String id, String nickname, String date) {
        this.id = id;
        this.nickname = nickname;
        this.joinedDate = date;
        this.friends = new ArrayList<>();
        this.badges = new ArrayList<>();
    }

    // Геттеры и сеттеры
    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getNickname() {
        return nickname;
    }

    public void setNickname(String nickname) {
        this.nickname = nickname;
    }

    public String getJoinedDate() {
        return joinedDate;
    }

    public void setJoinedDate(String joinedDate) {
        this.joinedDate = joinedDate;
    }

    public List<String> getFriends() {
        return friends;
    }

    public void setFriends(List<String> friends) {
        this.friends = friends;
    }

    public List<String> getBadges() {
        return badges;
    }

    public void setBadges(List<String> badges) {
        this.badges = badges;
    }

    public static CommunityProfile createProfile(String id, String nickname, String date) {
        return new CommunityProfile(id, nickname, date);
    }

    public void addFriend(String friendId) {
        try {
            if (friendId == null || friendId.trim().isEmpty()) {
                throw new IllegalArgumentException("Friend ID cannot be empty.");
            }
            friends.add(friendId);
        } catch (Exception ex) {
            System.out.println("Error adding friend: " + ex.getMessage());
        }
    }

    public void awardBadge(String badge) {
        if (badge != null && !badge.trim().isEmpty()) {
            badges.add(badge);
        }
    }

    public void showProfileInfo() {
        System.out.println(id + " — " + nickname + ", joined " + joinedDate);
    }
}